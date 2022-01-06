obj-m	:= esp32_power.o
export ARCH=arm64
export CROSS_COMPILE=aarch64-buildroot-linux-gnu-
KERNELDIR ?= /home/tony/Arm/rock_pi/linux-5.10.10
PWD       := $(shell pwd)

CPPFLAGS += -include $(KERNELDIR)/include/generated/autoconf.h

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers *.order

