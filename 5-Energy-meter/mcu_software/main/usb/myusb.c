#include "myusb.h"
#include "o12864.h"
extern tony_interface_state_t tony_state;
extern uint8_t *g_usbRecvTb;
extern double g_i0, g_v0, g_i1, g_v1, g_w1;
double g_power = 0;
double g_peak = 0;
uint8_t g_workSt = 0;

osal_mutex_def_t mesBuffer;
osal_mutex_t mesLock;
#define mesEnter() do {osal_mutex_lock(mesLock,OSAL_TIMEOUT_WAIT_FOREVER); } while (0)
#define mesLeave() do {osal_mutex_unlock(mesLock); } while (0)
//#include "dcd.h"
static const char *TAG = "example";
enum {
  ITF_IN,
  ITF_OUT,
  ITF_NUM_TOTAL
};
void myusb_init(void) {

  tinyusb_config_t tusb_cfg = {
      .descriptor = NULL,
      .string_descriptor = NULL,
      .external_phy = false // In the most cases you need to use a `false` value
  };
  mesLock = osal_mutex_create(&mesBuffer);
  ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));
}
uint64_t tony_dataInIsr_user(uint32_t num, uint64_t cmd) {
  //usbd_edpt_xfer(tony_state.rhport,tony_state.ep_bulk_in,g_usbRecvTb,num);

  return usb_vcmd(cmd);
}
void startMes(void) {
  g_workSt = 1;
  g_power = 0.0;
  startShow();
  g_peak = 0;
}
void stopMes(void) {
  g_workSt = 0;
  stopShow();
}
uint64_t usb_vcmd(uint64_t cmd) {
  char *tstr = "OKOKOKOK";
  double ti0 = 123.456;
  double tv0 = 4123.456;
  uint64_t dru, *pdru;
  uint64_t cmdType = (cmd >> 32) & 0XFFFFFFFF;
  switch (cmdType) {
    case USB_VCMD_START:
      //OLED_ShowString(0,40,(unsigned char *)"started");
      startMes();
      return 1;
      break;
    case USB_VCMD_STOP:
      // OLED_ShowString(0,40,(unsigned char *)"stopped");
      stopMes();
      return 0;
    case USB_VCMD_I:

      pdru = (uint64_t * ) & g_i1;
      dru = *pdru;
      return dru;
      break;
    case USB_VCMD_V:pdru = (uint64_t * ) & (g_v1);
      dru = *pdru;
      return dru;
    case USB_VCMD_P:pdru = (uint64_t * ) & g_w1;
      dru = *pdru;
      return dru;
    case USB_VCMD_E:pdru = (uint64_t * ) & g_power;
      dru = *pdru;
      return dru;
    case USB_VCMD_PEAK:pdru = (uint64_t * ) & g_peak;
      dru = *pdru;
      return dru;
      break;
    default:return 0;
      break;
  }
  uint64_t *pru, ru;
  pru = (uint64_t *) tstr;
  ru = *pru;
  return ru;
}
void anaPower(void) {
  double temp_i;

  if (g_workSt) {
    temp_i = g_i0 + g_i1;
    g_power += temp_i * g_v1 * 0.001 * 0.001 * 0.001;
    if (g_w1 > g_peak) {
      g_peak = g_w1;
    }
  }
}