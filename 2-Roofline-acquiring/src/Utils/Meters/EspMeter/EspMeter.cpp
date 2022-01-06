#include <Utils/Meters/EspMeter/EspMeter.hpp>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define DEVICE_NAME "/dev/esp32_power"
#include <signal.h>
using namespace DIVERSE_METER;
enum {
  USB_VCMD_START = 1,
  USB_VCMD_STOP,
  USB_VCMD_I,
  USB_VCMD_V,
  USB_VCMD_P,
  USB_VCMD_E,
  USB_VCMD_PEAK,

};
EspMeter::EspMeter(/* args */) {
  devFd = open(DEVICE_NAME, O_RDWR);
  if (devFd == -1) {

    METER_ERROR("can not open device meter");
  }
}

EspMeter::EspMeter(string name) {
  devFd = open(name.data(), O_RDWR);
  if (devFd == -1) {

    METER_ERROR("can not open device meter");
  }
}
EspMeter::~EspMeter() {
  if (devFd != -1) {
    close(devFd);
  }
}
uint64_t EspMeter::accessEsp32(uint64_t cmd) {
  if (devFd == -1) {
    return 0;
  }
  uint8_t *ptr = (uint8_t *) &cmd;
  write(devFd, ptr, 8);
  char recv[64];
  read(devFd, recv, 8);
  uint64_t ru, *pru;
  pru = (uint64_t *) recv;
  ru = *pru;
  return ru;
}
void EspMeter::startMeter() {
  uint64_t cmdStart = (uint64_t) USB_VCMD_START;
  cmdStart = cmdStart << 32;
  accessEsp32(cmdStart);
}
void EspMeter::stopMeter() {
  uint64_t cmdStart = (uint64_t) USB_VCMD_STOP;
  cmdStart = cmdStart << 32;
  accessEsp32(cmdStart);
}
double EspMeter::getI() {
  uint64_t cmdStart = (uint64_t) USB_VCMD_I;
  cmdStart = cmdStart << 32;
  uint64_t ru = accessEsp32(cmdStart);
  double dru, *pdru;
  pdru = (double *) &ru;
  dru = *pdru;
  return dru;
}

double EspMeter::getV() {
  uint64_t cmdStart = (uint64_t) USB_VCMD_V;
  cmdStart = cmdStart << 32;
  uint64_t ru = accessEsp32(cmdStart);
  double dru, *pdru;
  pdru = (double *) &ru;
  dru = *pdru;
  return dru;
}

double EspMeter::getP() {
  uint64_t cmdStart = (uint64_t) USB_VCMD_P;
  cmdStart = cmdStart << 32;
  uint64_t ru = accessEsp32(cmdStart);
  double dru, *pdru;
  pdru = (double *) &ru;
  dru = *pdru;
  return dru;
}

double EspMeter::getE() {
  uint64_t cmdStart = (uint64_t) USB_VCMD_E;
  cmdStart = cmdStart << 32;
  uint64_t ru = accessEsp32(cmdStart);
  double dru, *pdru;
  pdru = (double *) &ru;
  dru = *pdru;
  return dru;
}

double EspMeter::getPeak() {
  uint64_t cmdStart = (uint64_t) USB_VCMD_PEAK;
  cmdStart = cmdStart << 32;
  uint64_t ru = accessEsp32(cmdStart);
  double dru, *pdru;
  pdru = (double *) &ru;
  dru = *pdru;
  return dru;
}