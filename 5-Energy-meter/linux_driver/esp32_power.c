/*
 * USB esp32_powereton driver - 2.2
 *
 * Copyright (C) 2001-2004 Greg Kroah-Hartman (greg@kroah.com)
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License as
 *	published by the Free Software Foundation, version 2.
 *
 * This driver is based on the 2.6.3 version of drivers/usb/usb-esp32_powereton.c
 * but has been rewritten to be easier to read and use.
 *
 */

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
#include <linux/uaccess.h>
#include <linux/usb.h>
#include <linux/mutex.h>


/* Define these values to match your devices */
#define USB_esp32_power_VENDOR_ID    0x8227
#define USB_esp32_power_PRODUCT_ID    0x8227

/* table of devices that work with this driver */
static const struct usb_device_id esp32_power_table[] = {
    {USB_DEVICE(USB_esp32_power_VENDOR_ID, USB_esp32_power_PRODUCT_ID)},
    {}                    /* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, esp32_power_table
);


/* Get a minor range for your devices from the usb maintainer */
#define USB_esp32_power_MINOR_BASE    192

/* our private defines. if this grows any larger, use your own .h file */
#define MAX_TRANSFER        (PAGE_SIZE - 512)
/* MAX_TRANSFER is chosen so that the VM is not stressed by
   allocations > PAGE_SIZE and the number of packets in a page
   is an integer 512 is the largest possible packet on EHCI */
#define WRITES_IN_FLIGHT    8
/* arbitrarily chosen */
static struct fasync_struct *g_async;
/* Structure to hold all of our device specific stuff */
struct usb_esp32_power {
  struct usb_device *udev;            /* the usb device for this device */
  struct usb_interface *interface;        /* the interface for this device */
  struct semaphore limit_sem;        /* limiting the number of writes in progress */
  struct usb_anchor submitted;        /* in case we need to retract our submissions */
  struct urb *bulk_in_urb, *irqUrb;        /* the urb to read data with */
  unsigned char *bulk_in_buffer, *isrBuffer;    /* the buffer to receive data */
  size_t bulk_in_size;        /* the size of the receive buffer */
  size_t bulk_in_filled;        /* number of bytes in the buffer */
  size_t bulk_in_copied;        /* already copied to user space */
  __u8 bulk_in_endpointAddr;    /* the address of the bulk in endpoint */
  __u8 bulk_out_endpointAddr;    /* the address of the bulk out endpoint */
  int errors;            /* the last request tanked */
  bool ongoing_read;        /* a read is going on */
  spinlock_t err_lock;        /* lock for errors */
  struct kref kref;
  struct mutex io_mutex;        /* synchronize I/O with disconnect */
  wait_queue_head_t bulk_in_wait;        /* to wait for an ongoing read */
//struct fasync_struct *tt_async;
};
#define to_esp32_power_dev(d) container_of(d, struct usb_esp32_power, kref)

static struct usb_driver esp32_power_driver;
static void esp32_power_draw_down(struct usb_esp32_power *dev);

static void esp32_power_delete(struct kref *kref) {
  struct usb_esp32_power *dev = to_esp32_power_dev(kref);

  usb_free_urb(dev->bulk_in_urb);
  //usb_free_urb(dev->irqUrb);
  usb_put_dev(dev->udev);
  kfree(dev->bulk_in_buffer);
  //kfree(dev->isrBuffer);
  kfree(dev);
}

static int esp32_power_open(struct inode *inode, struct file *file) {
  struct usb_esp32_power *dev;
  struct usb_interface *interface;
  int subminor;
  int retval = 0;
  //printk("try open esp32_power\n");
  try_module_get(THIS_MODULE);

  subminor = iminor(inode);

  interface = usb_find_interface(&esp32_power_driver, subminor);
  if (!interface) {
    printk("%s - error, can't find device for minor %d\n", subminor);
    retval = -ENODEV;
    goto exit;
  }

  dev = usb_get_intfdata(interface);

  if (!dev) {
    retval = -ENODEV;
    goto exit;
  }

  retval = usb_autopm_get_interface(interface);
  if (retval)
    goto exit;

  /* increment our usage count for the device */
  kref_get(&dev->kref);

  /* save our object in the file's private structure */
  file->private_data = dev;

  exit:
  return retval;
}

static int esp32_power_release(struct inode *inode, struct file *file) {
  struct usb_esp32_power *dev;

  dev = file->private_data;
  if (dev == NULL)
    return -ENODEV;

  /* allow the device to be autosuspended */
  mutex_lock(&dev->io_mutex);
  if (dev->interface)
    usb_autopm_put_interface(dev->interface);
  mutex_unlock(&dev->io_mutex);

  /* decrement the count on our device */
  kref_put(&dev->kref, esp32_power_delete);
  return 0;
}

static int esp32_power_flush(struct file *file, fl_owner_t id) {
  struct usb_esp32_power *dev;
  int res;

  dev = file->private_data;
  if (dev == NULL)
    return -ENODEV;

  /* wait for io to stop */
  mutex_lock(&dev->io_mutex);
  esp32_power_draw_down(dev);

  /* read out errors, leave subsequent opens a clean slate */
  spin_lock_irq(&dev->err_lock);
  res = dev->errors ? (dev->errors == -EPIPE ? -EPIPE : -EIO) : 0;
  dev->errors = 0;
  spin_unlock_irq(&dev->err_lock);

  mutex_unlock(&dev->io_mutex);

  return res;
}

static void esp32_power_read_bulk_callback(struct urb *urb) {
  struct usb_esp32_power *dev;

  dev = urb->context;

  spin_lock(&dev->err_lock);
  /* sync/async unlink faults aren't errors */
  if (urb->status) {
    if (!(urb->status == -ENOENT ||
        urb->status == -ECONNRESET ||
        urb->status == -ESHUTDOWN))
      dev_err(&dev->interface->dev,
              "%s - nonzero write bulk status received: %d\n",
              __func__, urb->status);

    dev->errors = urb->status;
  } else {
    dev->bulk_in_filled = urb->actual_length;
  }
  dev->ongoing_read = 0;
  spin_unlock(&dev->err_lock);

  wake_up_interruptible(&dev->bulk_in_wait);
}

static int esp32_power_do_read_io(struct usb_esp32_power *dev, size_t count) {
  int rv;

  /* prepare a read */
  usb_fill_bulk_urb(dev->bulk_in_urb,
                    dev->udev,
                    usb_rcvbulkpipe(dev->udev,
                                    dev->bulk_in_endpointAddr),
                    dev->bulk_in_buffer,
                    min(dev->bulk_in_size, count),
                    esp32_power_read_bulk_callback,
                    dev);
  /* tell everybody to leave the URB alone */
  spin_lock_irq(&dev->err_lock);
  dev->ongoing_read = 1;
  spin_unlock_irq(&dev->err_lock);

  /* submit bulk in urb, which means no data to deliver */
  dev->bulk_in_filled = 0;
  dev->bulk_in_copied = 0;

  /* do it */
  rv = usb_submit_urb(dev->bulk_in_urb, GFP_KERNEL);
  if (rv < 0) {
    dev_err(&dev->interface->dev,
            "%s - failed submitting read urb, error %d\n",
            __func__, rv);
    rv = (rv == -ENOMEM) ? rv : -EIO;
    spin_lock_irq(&dev->err_lock);
    dev->ongoing_read = 0;
    spin_unlock_irq(&dev->err_lock);
  }

  return rv;
}

static ssize_t esp32_power_read(struct file *file, char *buffer, size_t count,
                                loff_t *ppos) {
  struct usb_esp32_power *dev;
  int rv;
  bool ongoing_io;

  dev = file->private_data;

  /* if we cannot read at all, return EOF */
  if (!dev->bulk_in_urb || !count)
    return 0;

  /* no concurrent readers */
  rv = mutex_lock_interruptible(&dev->io_mutex);
  if (rv < 0)
    return rv;

  if (!dev->interface) {        /* disconnect() was called */
    rv = -ENODEV;
    goto exit;
  }

  /* if IO is under way, we must not touch things */
  retry:
  spin_lock_irq(&dev->err_lock);
  ongoing_io = dev->ongoing_read;
  spin_unlock_irq(&dev->err_lock);

  if (ongoing_io) {
    /* nonblocking IO shall not wait */
    if (file->f_flags & O_NONBLOCK) {
      rv = -EAGAIN;
      goto exit;
    }
    /*
     * IO may take forever
     * hence wait in an interruptible state
     */
    rv = wait_event_interruptible(dev->bulk_in_wait, (!dev->ongoing_read));
    if (rv < 0)
      goto exit;
  }

  /* errors must be reported */
  rv = dev->errors;
  if (rv < 0) {
    /* any error is reported once */
    dev->errors = 0;
    /* to preserve notifications about reset */
    rv = (rv == -EPIPE) ? rv : -EIO;
    /* report it */
    goto exit;
  }

  /*
   * if the buffer is filled we may satisfy the read
   * else we need to start IO
   */

  if (dev->bulk_in_filled) {
    /* we had read data */
    size_t available = dev->bulk_in_filled - dev->bulk_in_copied;
    size_t chunk = min(available, count);

    if (!available) {
      /*
       * all data has been used
       * actual IO needs to be done
       */
      rv = esp32_power_do_read_io(dev, count);
      if (rv < 0)
        goto exit;
      else
        goto retry;
    }
    /*
     * data is available
     * chunk tells us how much shall be copied
     */

    if (copy_to_user(buffer,
                     dev->bulk_in_buffer + dev->bulk_in_copied,
                     chunk))
      rv = -EFAULT;
    else
      rv = chunk;

    dev->bulk_in_copied += chunk;

    /*
     * if we are asked for more than we have,
     * we start IO but don't wait
     */
    if (available < count)
      esp32_power_do_read_io(dev, count - chunk);
  } else {
    /* no data in the buffer */
    rv = esp32_power_do_read_io(dev, count);
    if (rv < 0)
      goto exit;
    else
      goto retry;
  }
  exit:
  mutex_unlock(&dev->io_mutex);
  return rv;
}

static void esp32_power_write_bulk_callback(struct urb *urb) {
  struct usb_esp32_power *dev;

  dev = urb->context;

  /* sync/async unlink faults aren't errors */
  if (urb->status) {
    if (!(urb->status == -ENOENT ||
        urb->status == -ECONNRESET ||
        urb->status == -ESHUTDOWN))
      dev_err(&dev->interface->dev,
              "%s - nonzero write bulk status received: %d\n",
              __func__, urb->status);

    spin_lock(&dev->err_lock);
    dev->errors = urb->status;
    spin_unlock(&dev->err_lock);
  }

  /* free up our allocated buffer */
  usb_free_coherent(urb->dev, urb->transfer_buffer_length,
                    urb->transfer_buffer, urb->transfer_dma);
  up(&dev->limit_sem);
}

static ssize_t esp32_power_write(struct file *file, const char *user_buffer,
                                 size_t count, loff_t *ppos) {
  struct usb_esp32_power *dev;
  int retval = 0;
  struct urb *urb = NULL;
  char *buf = NULL;
  size_t writesize = min(count, (size_t)MAX_TRANSFER);

  dev = file->private_data;

  /* verify that we actually have some data to write */
  if (count == 0)
    goto exit;

  /*
   * limit the number of URBs in flight to stop a user from using up all
   * RAM
   */
  if (!(file->f_flags & O_NONBLOCK)) {
    if (down_interruptible(&dev->limit_sem)) {
      retval = -ERESTARTSYS;
      goto exit;
    }
  } else {
    if (down_trylock(&dev->limit_sem)) {
      retval = -EAGAIN;
      goto exit;
    }
  }

  spin_lock_irq(&dev->err_lock);
  retval = dev->errors;
  if (retval < 0) {
    /* any error is reported once */
    dev->errors = 0;
    /* to preserve notifications about reset */
    retval = (retval == -EPIPE) ? retval : -EIO;
  }
  spin_unlock_irq(&dev->err_lock);
  if (retval < 0)
    goto error;

  /* create a urb, and a buffer for it, and copy the data to the urb */
  urb = usb_alloc_urb(0, GFP_KERNEL);
  if (!urb) {
    retval = -ENOMEM;
    goto error;
  }

  buf = usb_alloc_coherent(dev->udev, writesize, GFP_KERNEL,
                           &urb->transfer_dma);
  if (!buf) {
    retval = -ENOMEM;
    goto error;
  }

  if (copy_from_user(buf, user_buffer, writesize)) {
    retval = -EFAULT;
    goto error;
  }

  /* this lock makes sure we don't submit URBs to gone devices */
  mutex_lock(&dev->io_mutex);
  if (!dev->interface) {        /* disconnect() was called */
    mutex_unlock(&dev->io_mutex);
    retval = -ENODEV;
    goto error;
  }

  /* initialize the urb properly */
  usb_fill_bulk_urb(urb, dev->udev,
                    usb_sndbulkpipe(dev->udev, dev->bulk_out_endpointAddr),
                    buf, writesize, esp32_power_write_bulk_callback, dev);
  urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
  usb_anchor_urb(urb, &dev->submitted);

  /* send the data out the bulk port */
  retval = usb_submit_urb(urb, GFP_KERNEL);
  mutex_unlock(&dev->io_mutex);
  if (retval) {
    dev_err(&dev->interface->dev,
            "%s - failed submitting write urb, error %d\n",
            __func__, retval);
    goto error_unanchor;
  }

  /*
   * release our reference to this urb, the USB core will eventually free
   * it entirely
   */
  usb_free_urb(urb);

  return writesize;

  error_unanchor:
  usb_unanchor_urb(urb);
  error:
  if (urb) {
    usb_free_coherent(dev->udev, writesize, buf, urb->transfer_dma);
    usb_free_urb(urb);
  }
  up(&dev->limit_sem);

  exit:
  return retval;
}

static int esp32_power_fasync(int fd, struct file *filp, int on) {
  /* struct usb_esp32_power *dev;


  dev = filp->private_data;*/
  return fasync_helper(fd, filp, on, &g_async);
}
static const struct file_operations esp32_power_fops = {
    .owner =    THIS_MODULE,
    .read =        esp32_power_read,
    .write =    esp32_power_write,
    .open =        esp32_power_open,
    .release =    esp32_power_release,
    .flush =    esp32_power_flush,
    .llseek =    noop_llseek,
    .fasync    = esp32_power_fasync,
};

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device registered with the driver core
 */
static struct usb_class_driver esp32_power_class = {
    .name =        "esp32_power",
    .fops =        &esp32_power_fops,
    .minor_base =    USB_esp32_power_MINOR_BASE,
};

static void usb_esp32_power_irq(struct urb *urb) {
  struct usb_esp32_power *dev = urb->context;
  int i;
  kill_fasync(&g_async, SIGIO, POLL_IN);
  switch (urb->status) {
    case 0:            /* success */
      break;
    case -ECONNRESET:    /* unlink */
    case -ENOENT:
    case -ESHUTDOWN: return;
      /* -EPIPE:  should clear the halt */
    default:        /* error */
      goto resubmit;
  }

  resubmit:
  usb_submit_urb(urb, GFP_ATOMIC);
}
static int esp32_power_probe(struct usb_interface *interface,
                             const struct usb_device_id *id) {
  struct usb_esp32_power *dev;
  struct usb_host_interface *iface_desc;
  struct usb_endpoint_descriptor *endpoint;
  size_t buffer_size;
  int i, pipe, maxp;
  int retval = -ENOMEM;

  /* allocate memory for our device state and initialize it */
  printk("envoke esp32_power probe \r\n");
  dev = kzalloc(sizeof(*dev), GFP_KERNEL);
  if (!dev)
    goto error;
  kref_init(&dev->kref);
  sema_init(&dev->limit_sem, WRITES_IN_FLIGHT);
  mutex_init(&dev->io_mutex);
  spin_lock_init(&dev->err_lock);
  init_usb_anchor(&dev->submitted);
  init_waitqueue_head(&dev->bulk_in_wait);

  dev->udev = usb_get_dev(interface_to_usbdev(interface));
  dev->interface = interface;
  iface_desc = interface->cur_altsetting;
  //irq

  /*endpoint = &iface_desc->endpoint[0].desc;
  pipe = usb_rcvintpipe(dev->udev, endpoint->bEndpointAddress);
  maxp = usb_maxpacket(dev->udev, pipe, usb_pipeout(pipe));
  dev->irqUrb=usb_alloc_urb(0, GFP_KERNEL);
  buffer_size = usb_endpoint_maxp(endpoint);
  dev->isrBuffer = kmalloc(buffer_size, GFP_KERNEL);
  usb_fill_int_urb(dev->irqUrb, dev->udev, pipe,
           dev->isrBuffer, (maxp > 8 ? 8 : maxp),
           usb_esp32_power_irq,dev, endpoint->bInterval);*/
  /* set up the endpoint information */
  /* use only the first bulk-in and bulk-out endpoints */


  for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
    endpoint = &iface_desc->endpoint[i].desc;

    if (!dev->bulk_in_endpointAddr &&
        usb_endpoint_is_bulk_in(endpoint)) {
      /* we found a bulk in endpoint */
      buffer_size = usb_endpoint_maxp(endpoint);
      dev->bulk_in_size = buffer_size;
      dev->bulk_in_endpointAddr = endpoint->bEndpointAddress;
      dev->bulk_in_buffer = kmalloc(buffer_size, GFP_KERNEL);
      if (!dev->bulk_in_buffer)
        goto error;
      dev->bulk_in_urb = usb_alloc_urb(0, GFP_KERNEL);
      if (!dev->bulk_in_urb)
        goto error;
    }

    if (!dev->bulk_out_endpointAddr &&
        usb_endpoint_is_bulk_out(endpoint)) {
      /* we found a bulk out endpoint */
      dev->bulk_out_endpointAddr = endpoint->bEndpointAddress;
    }
  }
  if (!(dev->bulk_in_endpointAddr && dev->bulk_out_endpointAddr)) {
    dev_err(&interface->dev,
            "Could not find both bulk-in and bulk-out endpoints\n");
    goto error;
  }

  /* save our data pointer in this interface device */
  usb_set_intfdata(interface, dev);

  /* we can register the device now, as it is ready */
  retval = usb_register_dev(interface, &esp32_power_class);
  if (retval) {
    /* something prevented us from registering this driver */
    dev_err(&interface->dev,
            "Not able to get a minor for this device.\n");
    usb_set_intfdata(interface, NULL);
    goto error;
  }

  /* let the user know what node this device is now attached to */
  dev_info(&interface->dev,
           "USB esp32_powereton device now attached to USBesp32_power-%d",
           interface->minor);
  return 0;

  error:
  if (dev)
    /* this frees allocated memory */
    kref_put(&dev->kref, esp32_power_delete);
  return retval;
}

static void esp32_power_disconnect(struct usb_interface *interface) {
  struct usb_esp32_power *dev;
  int minor = interface->minor;

  dev = usb_get_intfdata(interface);
  usb_set_intfdata(interface, NULL);

  /* give back our minor */
  usb_deregister_dev(interface, &esp32_power_class);

  /* prevent more I/O from starting */
  mutex_lock(&dev->io_mutex);
  dev->interface = NULL;
  mutex_unlock(&dev->io_mutex);

  usb_kill_anchored_urbs(&dev->submitted);

  /* decrement our usage count */
  kref_put(&dev->kref, esp32_power_delete);

  dev_info(&interface->dev, "USB esp32_powereton #%d now disconnected", minor);
}

static void esp32_power_draw_down(struct usb_esp32_power *dev) {
  int time;

  time = usb_wait_anchor_empty_timeout(&dev->submitted, 1000);
  if (!time)
    usb_kill_anchored_urbs(&dev->submitted);
  usb_kill_urb(dev->bulk_in_urb);
}

static int esp32_power_suspend(struct usb_interface *intf, pm_message_t message) {
  struct usb_esp32_power *dev = usb_get_intfdata(intf);

  if (!dev)
    return 0;
  esp32_power_draw_down(dev);
  return 0;
}

static int esp32_power_resume(struct usb_interface *intf) {
  return 0;
}

static int esp32_power_pre_reset(struct usb_interface *intf) {
  struct usb_esp32_power *dev = usb_get_intfdata(intf);

  mutex_lock(&dev->io_mutex);
  esp32_power_draw_down(dev);

  return 0;
}

static int esp32_power_post_reset(struct usb_interface *intf) {
  struct usb_esp32_power *dev = usb_get_intfdata(intf);

  /* we are sure no URBs are active - no locking needed */
  dev->errors = -EPIPE;
  mutex_unlock(&dev->io_mutex);

  return 0;
}

static struct usb_driver esp32_power_driver = {
    .name =        "esp32_powereton",
    .probe =    esp32_power_probe,
    .disconnect =    esp32_power_disconnect,
    .suspend =    esp32_power_suspend,
    .resume =    esp32_power_resume,
    .pre_reset =    esp32_power_pre_reset,
    .post_reset =    esp32_power_post_reset,
    .id_table =    esp32_power_table,
    .supports_autosuspend = 1,
};

module_usb_driver(esp32_power_driver);

MODULE_LICENSE("GPL");
