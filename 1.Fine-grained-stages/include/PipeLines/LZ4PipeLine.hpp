#ifndef ADB_INCLUDE_PIPELINES_LZ4PIPELINE_HPP_
#define ADB_INCLUDE_PIPELINES_LZ4PIPELINE_HPP_
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <Utils/MemAddresser.hpp>
#include <CommonData/CommonData.hpp>
#include <PipeLines/AbstractPipeLine.hpp>
#include <CompressionComponents/LZ4Components.hpp>
using namespace std;
namespace ADB {
/*class:LZ4StageBase
description: The base class of all LZ4 stages,
as they share the same loop control,i.e., by processed bytes

date:202001020
*/
class LZ4StageBase : public AbstractPipeLineStage {
 protected:
  length_t loopCnt;
  length_t loopMax;
  uint32_t distance;
  uint32_t matchLen;
  LZ4ArgsPtr privateArg;
 public:
  MemAddresserPtr inStream;
  LZ4StageBase(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      AbstractPipeLineStage(cpu, inputQueue, outputQueue) {
    loopCnt = 0;
    loopMax = 0;
    privateArg = make_shared<LZ4Args>();
  }

  LZ4StageBase(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      AbstractPipeLineStage(cpu, _hasNextStage, prev, _ownQueSize) {
    loopCnt = 0;
    loopMax = 0;
    privateArg = make_shared<LZ4Args>();
  }
  void setLoop(length_t i) {
    privateArg->max_ptr = i;
  }
  double getIpm() {
    return getinLineIpm(privateArg->max_ptr);
  }
  void pipeLineFunction() {

  }
  bool shouldLoop() {
    if (privateArg->src_ptr < privateArg->max_ptr) {
      return true;
    }
    return false;
  }
  ~LZ4StageBase() {

  }
};
/*class:LZ4LoadStage
description: The pipeline stage of loading data and getmatch

date:202001013
*/
class LZ4LoadStage : public LZ4StageBase {
 public:

  ~LZ4LoadStage() {}
  LZ4LoadStage(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      LZ4StageBase(cpu, inputQueue, outputQueue) {

  }

  LZ4LoadStage(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      LZ4StageBase(cpu, _hasNextStage, prev, _ownQueSize) {

  }
  double getIpm() {
    return getinLineIpm(privateArg->max_ptr * 2);
  }
  void pipeLineFunction();

};
typedef std::shared_ptr<LZ4LoadStage> LZ4LoadStagePtr;

/*class:LZ4WriteStage
description: The pipeline stage of writing data
date:202001013
*/
class LZ4WriteStage : public LZ4StageBase {
 public:
  MemAddresserPtr outStream;
  ~LZ4WriteStage() {}
  LZ4WriteStage(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      LZ4StageBase(cpu, inputQueue, outputQueue) {

  }

  LZ4WriteStage(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      LZ4StageBase(cpu, _hasNextStage, prev, _ownQueSize) {

  }
  void pipeLineFunction();

};
typedef std::shared_ptr<LZ4WriteStage> LZ4WriteStagePtr;
/*class:LZ4PipeLine
description: The whole pipeline for LZ4
date:202001020
*/
class LZ4PipeLine : public AbstractPipeLine {
 private:
  /* data */
  ADB::length_t safetySize, stopPOS;
  LZ4LoadStagePtr s0;
  LZ4WriteStagePtr s1;
  QueueStagePtr passArg01, passArg12;
 public:
  MemAddresserPtr inStream, inStream2, outStream;
  LZ4PipeLine(/* args */);
  //void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void execute();
  ~LZ4PipeLine();
  LZ4PipeLine(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
};
typedef std::shared_ptr<LZ4PipeLine> LZ4PipeLinePtr;
}

#endif