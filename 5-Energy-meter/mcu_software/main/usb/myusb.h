#ifndef _MYUSB_H_
#define _MYUSB_H_

#include <stdlib.h>
#include "tonyusb.h"
//#include "tusb_cdc_acm.h"
void myusb_init(void);
uint64_t usb_vcmd(uint64_t cmd);
enum {
  USB_VCMD_START = 1,
  USB_VCMD_STOP,
  USB_VCMD_I,
  USB_VCMD_V,
  USB_VCMD_P,
  USB_VCMD_E,
  USB_VCMD_PEAK,

};
void anaPower(void);
void startMes(void);
void stopMes(void);
void startShow(void);
void stopShow(void);
#endif