#ifndef ADB_INCLUDE_COMPRESSIONTASKS_ABSTRACTTASK_HPP_
#define ADB_INCLUDE_COMPRESSIONTASKS_ABSTRACTTASK_HPP_
#include <CommonData/CommonData.hpp>
#include <CompressionComponents/AbstractComponent.hpp>
#include <Utils/MemAddresser.hpp>
#include <vector>
#include <Utils/TimeTestBench.hpp>
using namespace std;
namespace ADB {
/*class:AbstractTask
  description: container of AbstractTask
  input:null
  output:null
  date:20210930
  */
#define addForwardComponent(n)  myComponent.push_back(n)
#define getForwardComponent(i)   myComponent[i]
#define getBackwardComponent(i)  myComponentBackward[i]
#define addBackwardComponent(n)  myComponentBackward.push_back(n)
#define forwardSize()  myComponent.size()
#define backwardSize() myComponentBackward.size()
typedef std::shared_ptr<std::vector<AbstractComponentPtr>> compListPtr;
class AbstractTask {
 protected:

  /* data */
  compListPtr compPtrFor, compPtrBack;

  std::vector<AbstractComponentPtr> myComponent;
  std::vector<AbstractComponentPtr> myComponentBackward;
  std::vector<AbstractComponentPtr> forwardPrepare;
  std::vector<AbstractComponentPtr> backwardPrepare;

  ADB::length_t safetySize, stopPOS;
  TimeTestBench tb;
  memPtr mySrc, myDest;
 public:
  MemAddresserPtr inStream, outStream;
  void *otherPtr;
  AbstractTask(/* args */);
  ~AbstractTask();
  AbstractTask(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  length_t runForwardTask(void);
  length_t runBackwardTask(void);
  length_t profileForwardTask(void);
  length_t profileBackwardTask(void);
  void printProfile(void);
  void printBackwardProfile(void);

  /*void addForwardComponent(AbstractComponentPtr cp)
  {
      myComponent.push_back(cp);
  }
   void addBackwardComponent(AbstractComponentPtr cp)
  {
     myComponentBackward.push_back(cp);
  }
  AbstractComponentPtr getForwardComponent(size_t i)
  {
    return myComponent[i];
  }
  AbstractComponentPtr getBackwardComponent(size_t i)
  {
    return myComponentBackward[i];
  }
  length_t forwardSize(void)
  {
    return myComponent.size();
  }
  length_t backwardSize(void)
  {
    return myComponentBackward.size();
  }*/
  /*virtual length_t runForwardTask(void);
  virtual  length_t runBackwardTask(void);*/

};

}

#endif