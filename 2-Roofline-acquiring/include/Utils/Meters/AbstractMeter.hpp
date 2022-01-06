#ifndef ADB_INCLUDE_UTILS_AbstractMeter_HPP_
#define ADB_INCLUDE_UTILS_AbstractMeter_HPP_
#include <Utils/Logger.hpp>
#include <stdio.h>
#include <stdlib.h>
#define METER_ERROR(n) printf ("%s\r\n",n)

#include <Utils/UtilityFunctions.hpp>
using namespace std;
namespace DIVERSE_METER {

/*class:AbstractMeter
description:the entity of an abstract power meter, providing all function including:
E,PeakPower
note: the meter and bus rate is about 1ms
date:20211202
*/
class AbstractMeter {
 private:
  
 public:
  AbstractMeter(/* args */)
  {

  }
  //if exist in another name
 
  ~AbstractMeter()
  {

  }
  virtual void startMeter()
  {

  }
  virtual void stopMeter()
  {

  }
  //energy in J
  virtual double getE()
  {
    return 0.0;
  }
  //peak power in mW
  virtual double getPeak()
  {
    return 0.0;
  }

  virtual bool isValid() {
    return false;
  }
};
typedef std::shared_ptr<AbstractMeter> AbstractMeterPtr;

}

#endif