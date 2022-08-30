#include <Utils/Meters/Ltc2946Meter/Ltc2946Meter.hpp>
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
#define DEVICE_NAME "/dev/i2c-2"
#include <signal.h>

using namespace DIVERSE_METER;

Ltc2946Meter::Ltc2946Meter(/* args */) {
  devFd = open(DEVICE_NAME, O_RDWR);
  if (devFd == -1) {

    METER_ERROR("can not open device meter");
  }
  if (ioctl(devFd, I2C_SLAVE_FORCE, chipAddr) < 0) {
    METER_ERROR("Failed to access bus.\n");
    close(devFd);
    devFd = -1;
  }

}

Ltc2946Meter::Ltc2946Meter(string name) {
  devFd = open(name.data(), O_RDWR);
  if (devFd == -1) {

    METER_ERROR("can not open device meter");
  }
  if (ioctl(devFd, I2C_SLAVE_FORCE, chipAddr) < 0) {
    METER_ERROR("Failed to access bus.\n");
    close(devFd);
    devFd = -1;
  }

}
Ltc2946Meter::~Ltc2946Meter() {
  if (devFd != -1) {
    close(devFd);
  }
}
uint8_t Ltc2946Meter::readReg(uint8_t reg) {
  //ioctl(devFd, I2C_PEC, 1) ;
//i2c_smbus_write_byte(devFd,reg);
//i2c_smbus_write_byte(devFd,reg);
  return i2c_smbus_read_byte_data(devFd, reg);

}
void Ltc2946Meter::writeReg(uint8_t addr, uint8_t value) {
  i2c_smbus_write_byte_data(devFd, addr, value);
}
void Ltc2946Meter::startMeter() {
  //uint8_t ru=readReg(0x1e);
  //printf("reg 0x1e=%x\r\n",ru);
  //555
  writeReg(0x3c, 0);
  writeReg(0x3d, 0);
  writeReg(0x3e, 0);
  writeReg(0x3f, 0);
}
void Ltc2946Meter::stopMeter() {
  energy = getE_now();
}
double Ltc2946Meter::getI() {
  uint8_t msb = readReg(0x14);
  uint8_t lsb = readReg(0x15);

  int32_t value = 0;
  value = (msb << 4) | (lsb >> 4);

  double tv = value;
  tv = tv * 1.25;
  return tv;

}

double Ltc2946Meter::getV() {
  uint8_t msb = readReg(0x1e);
  uint8_t lsb = readReg(0x1f);

  int32_t value = 0;
  value = (msb << 4) | (lsb >> 4);

  double tv = value;
  tv = tv * 25;
  return tv;
}

double Ltc2946Meter::getP() {
  uint8_t msb2 = readReg(0x05);
  uint8_t msb1 = readReg(0x06);
  uint8_t lsb = readReg(0x07);
  int32_t value = msb2;
  value = (value << 8) | msb1;
  value = (value << 8) | lsb;

  double tv = value;
  tv = tv * 0.03125;
  return tv;
  //return 0.0;
}

double Ltc2946Meter::getE_now() {
  uint8_t msb3 = readReg(0x3C);
  uint8_t msb2 = readReg(0x3D);
  uint8_t msb1 = readReg(0x3E);
  uint8_t lsb = readReg(0x3F);
  int32_t value = msb3;
  value = (value << 8) | msb2;
  value = (value << 8) | msb1;
  value = (value << 8) | lsb;
  double tv = value;
  tv = tv * 0.033578;
  return tv;
  //return 0.0;
}
double Ltc2946Meter::getE() {
  return energy;
}
double Ltc2946Meter::getPeak() {
  uint8_t msb2 = readReg(0x08);
  uint8_t msb1 = readReg(0x09);
  uint8_t lsb = readReg(0x0A);
  int32_t value = msb2;
  value = (value << 8) | msb1;
  value = (value << 8) | lsb;

  double tv = value;
  tv = tv * 0.03125;
  return tv;
}