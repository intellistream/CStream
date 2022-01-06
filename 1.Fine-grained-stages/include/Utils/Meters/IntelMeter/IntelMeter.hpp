#ifndef ADB_INCLUDE_UTILS_IntelMeter_HPP_
#define ADB_INCLUDE_UTILS_IntelMeter_HPP_
#include <Utils/Logger.hpp>

#include <Utils/Meters/AbstractMeter.hpp>
#include <Utils/UtilityFunctions.hpp>
#include <vector>
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
#include <signal.h>
using namespace std;
namespace DIVERSE_METER {
typedef struct rapl_power_unit{
    double PU;       //power units
    double ESU;      //energy status units
    double TU;       //time units
} rapl_power_unit;
/*class:IntelMeter
description:the entity of intel msr-based power meter, providing all function including:
E,PeakPower
note: the meter and bus rate is about 1ms, you must run on intel x64 with modprobe msr and cpuid
date:20211202
*/
class IntelMeter:public AbstractMeter  {
 private:
  int devFd;
 uint64_t rdmsr(int cpu, uint32_t reg);
 rapl_power_unit get_rapl_power_unit();
 double eSum=0;

 uint32_t maxCpu=0;
 vector <int> cpus;
 vector <double> st;
 vector <double> en;
 vector <double> count;
 rapl_power_unit power_units;
 public:
  IntelMeter(/* args */);
  //if exist in another name
  IntelMeter(string name);
  ~IntelMeter();
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
 // double getPeak();

  bool isValid() {
    return (devFd != -1);
  }
};
typedef std::shared_ptr<IntelMeter> IntelMeterPtr;

}

#endif