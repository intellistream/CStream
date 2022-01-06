#include "tonyusb.h"


tony_interface_state_t tony_state ;

osal_mutex_def_t tonyLockBuffer;
osal_mutex_t tonyLock;
uint8_t g_usbRecvTb[64];
// Our own private lock, mostly for the state variable.
#define criticalEnter() do {osal_mutex_lock(tonyLock,OSAL_TIMEOUT_WAIT_FOREVER); } while (0)
#define criticalLeave() do {osal_mutex_unlock(tonyLock); } while (0)
bool atomicChangeState(tony_state_enum expectedState, tony_state_enum newState)
{
  bool ret = true;
  criticalEnter();
  tony_state_enum oldState = tony_state.state;
  if (oldState == expectedState)
  {
    tony_state.state = newState;
  }
  else
  {
    ret = false;
  }
  criticalLeave();
  return ret;
}
bool tud_tony_start_bus_read()
{
  tony_state_enum oldState = tony_state.state;
  switch(oldState)
  {
  // These may transition to IDLE
  case STATE_NAK:
  case STATE_ABORTING_BULK_IN_ABORTED:
    TU_VERIFY(atomicChangeState(oldState, STATE_IDLE));
    break;
  // When receiving, let it remain receiving
  case STATE_RCV:
    break;
  default:
    TU_VERIFY(false);
  }
  memset(g_usbRecvTb,0,64);
  TU_VERIFY(usbd_edpt_xfer(tony_state.rhport, tony_state.ep_bulk_out, g_usbRecvTb, 64));
 // TU_VERIFY(usbd_edpt_xfer(tony_state.rhport, tony_state.ep_bulk_out, tb, 64));
 
 
  return true;
}

void tony_init_cb(void)
{
  
    tonyLock = osal_mutex_create(&tonyLockBuffer);
    printf("INIT TONY CB\r\n");
}


void tony_reset_cb(uint8_t rhport)
{
  (void)rhport;
 
  
}
uint16_t tony_open_cb(uint8_t rhport, tusb_desc_interface_t const * itf_desc, uint16_t max_len)
{
  (void)rhport;

  uint16_t drv_len;
  uint8_t const * p_desc;
  uint8_t found_endpoints = 0;
  // Interface
  drv_len = 0u;
  p_desc = (uint8_t const *) itf_desc;

  tony_state.itf_id = itf_desc->bInterfaceNumber;
  tony_state.rhport = rhport;

  while (found_endpoints < itf_desc->bNumEndpoints && drv_len <= max_len)
  {
    if ( TUSB_DESC_ENDPOINT == p_desc[DESC_OFFSET_TYPE])
    {
      tusb_desc_endpoint_t const *ep_desc = (tusb_desc_endpoint_t const *)p_desc;
      switch(ep_desc->bmAttributes.xfer) {
        case TUSB_XFER_BULK:
         // TU_ASSERT(ep_desc->wMaxPacketSize.size == TONY_MAX_PACKET_SIZE, 0);
          if (tu_edpt_dir(ep_desc->bEndpointAddress) == TUSB_DIR_IN)
          {
            tony_state.ep_bulk_in = ep_desc->bEndpointAddress;
          } else {
            tony_state.ep_bulk_out = ep_desc->bEndpointAddress;
          }

          break;
        case TUSB_XFER_INTERRUPT:

          tony_state.ep_int_in = ep_desc->bEndpointAddress;
          break;
        default:
          TU_ASSERT(false, 0);
      }
      TU_ASSERT( usbd_edpt_open(rhport, ep_desc), 0);
      found_endpoints++;
    }

    drv_len += tu_desc_len(p_desc);
    p_desc   = tu_desc_next(p_desc);
  }

  // bulk endpoints are required, but interrupt IN is optional
#ifndef NDEBUG
  TU_ASSERT(tony_state.ep_bulk_in  != 0, 0);
  TU_ASSERT(tony_state.ep_bulk_out != 0, 0);
  if (itf_desc->bNumEndpoints == 2)
  {
    TU_ASSERT(tony_state.ep_int_in == 0, 0);
  }
  else if (itf_desc->bNumEndpoints == 3)
  {
    TU_ASSERT(tony_state.ep_int_in != 0, 0);
  }
#if (CFG_TUD_tony_ENABLE_488)
  if(tony_state.capabilities->bmIntfcCapabilities488.is488_2 ||
      tony_state.capabilities->bmDevCapabilities488.SR1)
  {
    TU_ASSERT(tony_state.ep_int_in != 0, 0);
  }
#endif
#endif
  atomicChangeState(STATE_CLOSED, STATE_NAK);
  tud_tony_open_cb(itf_desc->iInterface);

  return drv_len;
}
static volatile uint32_t bulkInStarted;
void tud_tony_open_cb(uint8_t interface_id)
{
  (void)interface_id;
  tud_tony_start_bus_read();
}

void tud_tony_bulkIn_clearFeature_cb(void)
{
}
void tud_tony_bulkOut_clearFeature_cb(void)
{
  tud_tony_start_bus_read();
}
bool tud_tony_initiate_abort_bulk_in_cb(uint8_t *tmcResult)
{
  bulkInStarted = 0;
  *tmcResult = TONY_STATUS_SUCCESS;
  return true;
}
bool tud_tony_check_abort_bulk_in_cb(tony_check_abort_bulk_rsp_t *rsp)
{
  (void)rsp;
  tud_tony_start_bus_read();
  return true;
}

bool tud_tony_initiate_abort_bulk_out_cb(uint8_t *tmcResult)
{
  *tmcResult = TONY_STATUS_SUCCESS;
  return true;

}
bool tud_tony_check_abort_bulk_out_cb(tony_check_abort_bulk_rsp_t *rsp)
{
  (void)rsp;
  tud_tony_start_bus_read();
  return true;
}
static volatile uint16_t queryState = 0;
static volatile uint32_t queryDelayStart;
static volatile uint32_t bulkInStarted;
static volatile uint32_t idnQuery;
static volatile uint8_t status;


bool tud_usbtmc_initiate_clear_cb(uint8_t *tmcResult)
{
  *tmcResult = TONY_STATUS_SUCCESS;
  queryState = 0;
  bulkInStarted = false;
  status = 0;
  return true;
}
// Invoked when a control transfer occurred on an interface of this class
// Driver response accordingly to the request and the transfer stage (setup/data/ack)
// return false to stall control endpoint (e.g unsupported request)
bool tony_control_xfer_cb(uint8_t rhport, uint8_t stage, tusb_control_request_t const * request)
{
  // nothing to do with DATA and ACK stage
  if ( stage != CONTROL_STAGE_SETUP ) return true;

  //uint8_t tmcStatusCode = TONY_STATUS_FAILED;


  if((request->bmRequestType_bit.type == TUSB_REQ_TYPE_STANDARD) &&
      (request->bmRequestType_bit.recipient == TUSB_REQ_RCPT_ENDPOINT) &&
      (request->bRequest == TUSB_REQ_CLEAR_FEATURE) &&
      (request->wValue == TUSB_REQ_FEATURE_EDPT_HALT))
  {
    uint32_t ep_addr = (request->wIndex);

    if(ep_addr == tony_state.ep_bulk_out)
    {
      criticalEnter();
      tony_state.state = STATE_NAK; // USBD core has placed EP in NAK state for us
      criticalLeave();
      tud_tony_bulkOut_clearFeature_cb();
    }
    else if (ep_addr == tony_state.ep_bulk_in)
    {
      tud_tony_bulkIn_clearFeature_cb();
    }
    else
    {
      return false;
    }
    return true;
  }

  // Otherwise, we only handle class requests.
  if(request->bmRequestType_bit.type != TUSB_REQ_TYPE_CLASS)
  {
    return false;
  }
  
  switch(request->bRequest)
  {
  // TONY required requests
  case TONY_bREQUEST_INITIATE_ABORT_BULK_OUT:
  {
    tony_initiate_abort_rsp_t rsp = {
        .bTag = tony_state.lastBulkOutTag,
    };
    TU_VERIFY(request->bmRequestType == 0xA2); // in,class,interface
    TU_VERIFY(request->wLength == sizeof(rsp));
    TU_VERIFY(request->wIndex == tony_state.ep_bulk_out);

    // wValue is the requested bTag to abort
    if(tony_state.state != STATE_RCV)
    {
      rsp.TONY_status = TONY_STATUS_FAILED;
    }
    else if(tony_state.lastBulkOutTag == (request->wValue & 0x7Fu))
    {
      rsp.TONY_status = TONY_STATUS_TRANSFER_NOT_IN_PROGRESS;
    }
    else
    {
      rsp.TONY_status = TONY_STATUS_SUCCESS;
      // Check if we've queued a short packet
      criticalEnter();
      tony_state.state = STATE_ABORTING_BULK_OUT;
      criticalLeave();
      //TU_VERIFY(tud_tony_initiate_abort_bulk_out_cb(&(rsp.TONY_status)));
      usbd_edpt_stall(rhport, tony_state.ep_bulk_out);
    }
    TU_VERIFY(tud_control_xfer(rhport, request, (void*)&rsp,sizeof(rsp)));
    return true;
  }

  case TONY_bREQUEST_CHECK_ABORT_BULK_OUT_STATUS:
  {
    tony_check_abort_bulk_rsp_t rsp = {
        .TONY_status = TONY_STATUS_SUCCESS,
        .NBYTES_RXD_TXD = tony_state.transfer_size_sent
    };
    TU_VERIFY(request->bmRequestType == 0xA2); // in,class,EP
    TU_VERIFY(request->wLength == sizeof(rsp));
    TU_VERIFY(request->wIndex == tony_state.ep_bulk_out);
    TU_VERIFY(tud_tony_check_abort_bulk_out_cb(&rsp));
    TU_VERIFY(tud_control_xfer(rhport, request, (void*)&rsp,sizeof(rsp)));
    return true;
  }

  case TONY_bREQUEST_INITIATE_ABORT_BULK_IN:
  {
    tony_initiate_abort_rsp_t rsp = {
        .bTag = tony_state.lastBulkInTag,
    };
    TU_VERIFY(request->bmRequestType == 0xA2); // in,class,interface
    TU_VERIFY(request->wLength == sizeof(rsp));
    TU_VERIFY(request->wIndex == tony_state.ep_bulk_in);
    // wValue is the requested bTag to abort
    if((tony_state.state == STATE_TX_REQUESTED || tony_state.state == STATE_TX_INITIATED) &&
        tony_state.lastBulkInTag == (request->wValue & 0x7Fu))
    {
      rsp.TONY_status = TONY_STATUS_SUCCESS;
    tony_state.transfer_size_remaining = 0u;
      // Check if we've queued a short packet
      criticalEnter();
      tony_state.state = ((tony_state.transfer_size_sent % TONY_MAX_PACKET_SIZE) == 0) ?
              STATE_ABORTING_BULK_IN : STATE_ABORTING_BULK_IN_SHORTED;
      criticalLeave();
      if(tony_state.transfer_size_sent  == 0)
      {
        // Send short packet, nothing is in the buffer yet
        TU_VERIFY( usbd_edpt_xfer(rhport, tony_state.ep_bulk_in, tony_state.ep_bulk_in_buf,(uint16_t)0u));
        tony_state.state = STATE_ABORTING_BULK_IN_SHORTED;
      }
      TU_VERIFY(tud_tony_initiate_abort_bulk_in_cb(&(rsp.TONY_status)));
    }
    else if((tony_state.state == STATE_TX_REQUESTED || tony_state.state == STATE_TX_INITIATED))
    { // FIXME: Unsure how to check  if the OUT endpoint fifo is non-empty....
      rsp.TONY_status = TONY_STATUS_TRANSFER_NOT_IN_PROGRESS;
    }
    else
    {
      rsp.TONY_status = TONY_STATUS_FAILED;
    }
    TU_VERIFY(tud_control_xfer(rhport, request, (void*)&rsp,sizeof(rsp)));
    return true;
  }

  case TONY_bREQUEST_CHECK_ABORT_BULK_IN_STATUS:
  {
    TU_VERIFY(request->bmRequestType == 0xA2); // in,class,EP
    TU_VERIFY(request->wLength == 8u);

    tony_check_abort_bulk_rsp_t rsp =
    {
        .TONY_status = TONY_STATUS_FAILED,
        .bmAbortBulkIn =
        {
            .BulkInFifoBytes = (tony_state.state != STATE_ABORTING_BULK_IN_ABORTED)
        },
        .NBYTES_RXD_TXD = tony_state.transfer_size_sent,
    };
    TU_VERIFY(tud_tony_check_abort_bulk_in_cb(&rsp));
    criticalEnter();
    switch(tony_state.state)
    {
    case STATE_ABORTING_BULK_IN_ABORTED:
      rsp.TONY_status = TONY_STATUS_SUCCESS;
      tony_state.state = STATE_IDLE;
      break;
    case STATE_ABORTING_BULK_IN:
    case STATE_ABORTING_BULK_OUT:
      rsp.TONY_status = TONY_STATUS_PENDING;
      break;
    default:
      break;
    }
    criticalLeave();
    TU_VERIFY(tud_control_xfer(rhport, request, (void*)&rsp,sizeof(rsp)));

    return true;
  }

  case TONY_bREQUEST_INITIATE_CLEAR:
    {
      TU_VERIFY(request->bmRequestType == 0xA1); // in,class,interface
     
      // After receiving an INITIATE_CLEAR request, the device must Halt the Bulk-OUT endpoint, queue the
      // control endpoint response shown in Table 31, and clear all input buffers and output buffers.
      usbd_edpt_stall(rhport, tony_state.ep_bulk_out);
      tony_state.transfer_size_remaining = 0;
      criticalEnter();
      tony_state.state = STATE_CLEARING;
      criticalLeave();
     // TU_VERIFY(tud_tony_initiate_clear_cb(&tonyStatusCode));
     // TU_VERIFY(tud_control_xfer(rhport, request, (void*)&tmcStatusCode,sizeof(tmcStatusCode)));
      return true;
    }

  case TONY_bREQUEST_CHECK_CLEAR_STATUS:
    {
      TU_VERIFY(request->bmRequestType == 0xA1); // in,class,interface
      tony_get_clear_status_rsp_t clearStatusRsp = {0};
      TU_VERIFY(request->wLength == sizeof(clearStatusRsp));

      if(usbd_edpt_busy(rhport, tony_state.ep_bulk_in))
      {
        // Stuff stuck in TX buffer?
        clearStatusRsp.bmClear.BulkInFifoBytes = 1;
        clearStatusRsp.TONY_status = TONY_STATUS_PENDING;
      }
      else
      {
        // Let app check if it's clear
        //TU_VERIFY(tud_tony_check_clear_cb(&clearStatusRsp));
      }
      if(clearStatusRsp.TONY_status == TONY_STATUS_SUCCESS)
      {
        criticalEnter();
        tony_state.state = STATE_IDLE;
        criticalLeave();
      }
      TU_VERIFY(tud_control_xfer(rhport, request, (void*)&clearStatusRsp,sizeof(clearStatusRsp)));
      return true;
    }

  // TONY Optional Requests
  default:
    TU_VERIFY(false);
    return false;
  }
  // Verification that we own the interface is unneeded since it's been routed to us specifically.
  return false;
}
bool tony_xfer_cb(uint8_t rhport, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes)
{
  
  TU_VERIFY(result == XFER_RESULT_SUCCESS);
  //uart_tx_str_sync("TMC XFER CB\r\n");
  if(tony_state.state == STATE_CLEARING) {
    return true; /* I think we can ignore everything here */
  }
 
  if(ep_addr == tony_state.ep_bulk_out)
  {

     //memset(tb,0,64);
     uint64_t *pCmd;
    usbd_edpt_xfer(rhport,tony_state.ep_bulk_out,g_usbRecvTb,xferred_bytes);
    pCmd=(uint64_t *)g_usbRecvTb;
    uint64_t cmd=*pCmd;
    uint64_t ru=tony_dataInIsr_user(xferred_bytes,cmd);
    uint8_t *ptr=(uint8_t *)&ru;
    usbd_edpt_xfer(rhport,tony_state.ep_bulk_in,ptr,8);
   // printf("bulk out %d:%s\r\n",xferred_bytes,g_usbRecvTb);
     
  }
  
  else if(ep_addr == tony_state.ep_bulk_in)
  {
    //printf("bulk in\r\n");
  }
  return true;
}