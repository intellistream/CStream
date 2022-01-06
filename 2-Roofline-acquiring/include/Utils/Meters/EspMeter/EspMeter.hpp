#ifndef ADB_INCLUDE_UTILS_EspMeter_HPP_
#define ADB_INCLUDE_UTILS_EspMeter_HPP_
#include <Utils/Logger.hpp>

#include <Utils/Meters/AbstractMeter.hpp>
#include <Utils/UtilityFunctions.hpp>
using namespace std;
namespace DIVERSE_METER {

/*class:EspMeter
description:the entity of an esp32s2-based power meter, providing all function including:
I,V,P,E,PeakPower
note: the meter and bus rate is about 1ms, you must have the esp_meter.ko
date:20211202
*/
class EspMeter:public AbstractMeter  {
 private:
  int devFd;
  uint64_t accessEsp32(uint64_t cmd);
 public:
  EspMeter(/* args */);
  //if exist in another name
  EspMeter(string name);
  ~EspMeter();
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
  //peak power in mW
  double getPeak();

  bool isValid() {
    return (devFd != -1);
  }
};
typedef std::shared_ptr<EspMeter> EspMeterPtr;

}

#endif