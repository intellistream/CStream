//
// Created by tony on 2021/9/28.
//

#ifndef ADB_INCLUDE_COMPRESSIONCOMPONENTS_ABSTRACTCOMPONENT_HPP_
#define ADB_INCLUDE_COMPRESSIONCOMPONENTS_ABSTRACTCOMPONENT_HPP_
#include <CommonData/CommonData.hpp>
#include <Utils/MemAddresser.hpp>
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <string>
using namespace std;
namespace ADB {
class compProfileInfo_t {
 public:
  length_t runTime, instructions, cacheMiss, branchMiss;
  compProfileInfo_t() {
    this->reset();
  }
  void reset();
  void printAll() {
    printf("%ld us", runTime);
  }
  void printHead() {
    printf("name\t|latency\t|\r\n");
  }
  compProfileInfo_t operator+(const compProfileInfo_t &a) {
    compProfileInfo_t ru;
    ru.runTime = this->runTime + a.runTime;
    return ru;
  }
};
typedef number_t compKey_t;
/*class:AbstractComponent
    description: container of AbstractComponent
    input:null
    output:null
    date:20210930
    */
class AbstractComponent {
 protected:
  MemAddresserPtr inStream, outStream;
  std::string nameTag;

  //add trace function here in the future
 public:
  compKey_t myKey;
  number_t myPreference;
  algo_type_t myType;
  compProfileInfo_t profileInfo;
  StageParseArgsPtr inArg, outArg;
  StageParseArgs midArg;
  AbstractComponent();
  AbstractComponent(compKey_t key,
                    number_t preference,
                    StageParseArgsPtr _inArg,
                    StageParseArgsPtr _outArg,
                    MemAddresserPtr _inStream,
                    MemAddresserPtr _outStream);

  ~AbstractComponent();

  virtual void exeFunction(void) = 0;
  virtual void writeArgFunction(void) = 0;

  void setName(string name);
  string getName(void);

};
typedef std::shared_ptr<AbstractComponent> AbstractComponentPtr;
}
#endif 
