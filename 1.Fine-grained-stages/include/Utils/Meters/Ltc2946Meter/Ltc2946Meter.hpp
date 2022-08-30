#ifndef ADB_INCLUDE_UTILS_Ltc2946Meter_HPP_
#define ADB_INCLUDE_UTILS_Ltc2946Meter_HPP_

#include <Utils/Meters/AbstractMeter.hpp>
#include <string>
#include <stdio.h>
#include <stdlib.h>   //exit()  
#include <fcntl.h>    //define O_RDWR  
#include <linux/i2c-dev.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
using namespace std;
namespace DIVERSE_METER {

/*class:Ltc2946Meter
description:the entity of an esp32s2-based power meter, providing all function including:
I,V,P,E,PeakPower
note: the meter and bus rate is about 1ms, you must have the esp_meter.ko
date:20211202
*/
class Ltc2946Meter : public AbstractMeter {
 private:
  int devFd;
  uint8_t readReg(uint8_t addr);
  void writeReg(uint8_t addr, uint8_t value);
  uint8_t chipAddr = 0x6f;
  char devBuf[32];
  double energy = 0.0;
  int32_t i2c_smbus_access(int file, char read_write, __u8 command,
                           int size, union i2c_smbus_data *data) {
    struct i2c_smbus_ioctl_data args;
    int32_t err;

    args.read_write = read_write;
    args.command = command;
    args.size = size;
    args.data = data;

    err = ioctl(file, I2C_SMBUS, &args);
    if (err == -1)
      err = -errno;
    return err;
  }

  __s32 i2c_smbus_read_byte_data(int file, __u8 command) {
    union i2c_smbus_data data;
    int err;

    err = i2c_smbus_access(file, I2C_SMBUS_READ, command,
                           I2C_SMBUS_BYTE_DATA, &data);
    if (err < 0)
      return err;

    return 0x0FF & data.byte;
  }

  __s32 i2c_smbus_write_byte_data(int file, __u8 command, __u8 value) {
    union i2c_smbus_data data;
    data.byte = value;
    return i2c_smbus_access(file, I2C_SMBUS_WRITE, command,
                            I2C_SMBUS_BYTE_DATA, &data);
  }

 public:
  Ltc2946Meter(/* args */);
  //if exist in another name
  Ltc2946Meter(string name);
  ~Ltc2946Meter();
  void startMeter();
  void stopMeter();
  //current in mA
  double getI();
  //voltage in mV
  double getV();
  //power in mW
  double getP();
  //energy in J
  double getE();
  double getE_now();
  //peak power in mW
  double getPeak();

  bool isValid() {
    return (devFd != -1);
  }
};
typedef std::shared_ptr<Ltc2946Meter> Ltc2946MeterPtr;

}

#endif