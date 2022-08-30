#ifndef ADB_INCLUDE_PIPELINES_ABSTRACTPIPELINE_HPP_
#define ADB_INCLUDE_PIPELINES_ABSTRACTPIPELINE_HPP_
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <Utils/MultiCore/SPSCQueue.hpp>
#include <Utils/MemAddresser.hpp>
#include <CommonData/CommonData.hpp>
#include <barrier>
#include <MeterHelp.hpp>
using namespace std;
using namespace ADB;
using namespace INTELLI;
namespace ADB {

typedef std::shared_ptr<SafeQueue<StageParseArgs>> SafeQueueStagePtr;
typedef std::shared_ptr<INTELLI::SPSCQueue<StageParseArgs>> QueueStagePtr;
//typedef std::shared_ptr<std::queue<StageParseArgs>> QueueStagePtr;
/*class:AbstractPipeLineStage
description: The base class of pipeline stage

date:2020011111
*/
class AbstractPipeLineStage;
typedef std::shared_ptr<AbstractPipeLineStage> AbstractPipeLineStagePtr;
class AbstractPipeLineStage : public AbstractThread {

 protected:
  StageParseArgs midArg;
  length_t stageNo, stageCnt;
  void threadMain();
  bool isLoaded;

  /*the pipeline interface function used for derived classed, needless to push & pop the que
  however, if under different behavior of queues, please rewrite the threadMain()*/
  virtual void pipeLineFunction();
  virtual void pipeLineInit() {

  }
  /* the condition function of wether continue*/
  virtual bool shouldLoop();
  BarrierPtr initBar = nullptr;
  bool hasPrevStage;
  bool hasNextStage;
  length_t ownQueSize;
 public:

  QueueStagePtr inputQueue, outputQueue;
  //auto fix the que assigned but not created
  void autoFixQueue();
  AbstractPipeLineStage(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue);
  AbstractPipeLineStage(length_t cpu, bool hasNextStage, AbstractPipeLineStagePtr prev, length_t ownQueSize);
  ~AbstractPipeLineStage() {

  }
  void setInitBar(BarrierPtr barPrev) {
    initBar = barPrev;

  }
  void waitInitBar(void) {
    if (initBar) {
      initBar->arrive_and_wait();
    }
  }
  void setStageNo(length_t _stageNo) {
    stageNo = _stageNo;
  }
  void join() {
    AbstractThread::join();
  }
  void detach() {
    AbstractThread::detach();
  }
  AbstractPipeLineStagePtr prevStage;
};

/*class:AbstractPipeLine
description: The base class of a whole pipeline

date:202001030
*/
class AbstractPipeLine {

 private:
  /* data */

  ADB::length_t safetySize, stopPOS, inSize;
 protected:
  std::vector<AbstractPipeLineStagePtr> stages;
  string subName;
  AbstractMeterPtr powerMeter = nullptr;
  int mainCpu;
  BarrierPtr initBar = nullptr;
 public:
  MemAddresserPtr inStream, outStream;
  uint64_t allRunTime;
  AbstractPipeLine();
  void makeBarrier() {
    initBar = UtilityFunctions::createBarrier(stages.size());
  }
  void creatQueues();
  //the function to start a pipeline process
  void execute();
  //run each stage sequentially to profile without block
  void seqProfile();
  //print the stage name,id, cpu bind and latency
  void printStages();
  //out put to csv file
  void outputStages2Csv(std::string fname);
  //rebind stages according to vector, called before execute or profile
  void rebindByVector(std::vector<int> rmv);
  ~AbstractPipeLine();
  AbstractPipeLine(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  //set up the power meter
  void setUpMeter();
  void setMainCpu(int cpu) {
    mainCpu = cpu;
  }
  //get the specific stage
  AbstractPipeLineStagePtr getStage(size_t n) {
    if (n <= stages.size()) {
      return stages[n];
    }
    return nullptr;
  }
  AbstractPipeLineStagePtr getStage(string name) {
    size_t i;
    size_t n = stages.size();
    for (i = 0; i < n; i++) {
      if (stages[i]->getName() == name) {
        return stages[i];
      }
    }

    return nullptr;
  }
};

}
#endif