#include "gaiacli.h"
#include "o12864.h"
#include "gfile.h"
#include "vm32_devs.h"
#include "mpu6050.h"
extern float g_pitch, g_roll, g_yaw;

ddot onedev_getPitch(void) {

  ddot ru = g_pitch;
  return ru;
}
ddot onedev_getRoll(void) {
  ddot ru = g_roll;
  return ru;
}
ddot onedev_getYall(void) {
  /* printf("f=%dMhz \r\n",240);
   return 240;*/
  ddot ru = g_yaw;
  return ru;
}
uint32_t onedev_delayms(uint32_t a) {
  delay_ms(a);
  return 0;
}
void vm32_addOneDev(VM32 *vm32) {
  VMDEV_DEV *odev = (VMDEV_DEV *) malloc(sizeof(VMDEV_DEV));
  vmdev_dev_init(odev, 1);
  vmdev_addDevtoMr(odev, &vm32->devMr);

  VMDEV_FUNC *func_pitch = (VMDEV_FUNC *) malloc(sizeof(VMDEV_FUNC));
  vmdev_func_init(func_pitch, 1);
  func_pitch->readDF = onedev_getPitch;
  vmdev_addFunctoDev(func_pitch, odev);

  VMDEV_FUNC *func_roll = (VMDEV_FUNC *) malloc(sizeof(VMDEV_FUNC));
  vmdev_func_init(func_roll, 2);
  func_roll->readDF = onedev_getRoll;
  vmdev_addFunctoDev(func_roll, odev);

  VMDEV_FUNC *func_yall = (VMDEV_FUNC *) malloc(sizeof(VMDEV_FUNC));
  vmdev_func_init(func_yall, 3);
  func_yall->readDF = onedev_getYall;
  vmdev_addFunctoDev(func_yall, odev);

  VMDEV_FUNC *func_delay = (VMDEV_FUNC *) malloc(sizeof(VMDEV_FUNC));
  vmdev_func_init(func_delay, 4);
  func_delay->writeU32 = onedev_delayms;
  vmdev_addFunctoDev(func_delay, odev);
} 