#ifndef ADB_INCLUDE_PIPELINES_TCOMP32PIPELINE_HPP_
#define ADB_INCLUDE_PIPELINES_TCOMP32PIPELINE_HPP_
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <Utils/MemAddresser.hpp>
#include <CommonData/CommonData.hpp>
#include <PipeLines/AbstractPipeLine.hpp>
#include <Utils/Cpp11Clock.hpp>
using namespace std;
using namespace CPP11_CLOCK;
namespace ADB {
/*class:Tcomp32StageBase
description: The base class of all tcomp32 stages,
as they share the same loop control,i.e., by processed bytes

date:202001013
*/
class Tcomp32StageBase : public AbstractPipeLineStage {
 protected:
  length_t loopCnt;
  length_t loopMax;
 public:

  Tcomp32StageBase(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      AbstractPipeLineStage(cpu, inputQueue, outputQueue) {
    loopCnt = 0;
    loopMax = 0;
  }

  Tcomp32StageBase(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      AbstractPipeLineStage(cpu, _hasNextStage, prev, _ownQueSize) {
    loopCnt = 0;
    loopMax = 0;
  }

  void setLoop(length_t i) {
    loopMax = i;
    loopCnt = 0;
  }
  void pipeLineFunction() {

    loopCnt++; //4 byte once

  }
  bool shouldLoop() {
    if (loopCnt < loopMax) {
      return true;
    }
    return false;
  }
  double getIpm() {
    return getinLineIpm(loopMax);
  }
  ~Tcomp32StageBase() {

  }
};
/*class:Tcomp32LoadStage
description: The pipeline stage of loading 32-bit data

date:202001112
*/
class Tcomp32LoadStage : public Tcomp32StageBase {
 private:
  int64_t timeBase = 0;
  Cpp11Clock clk;
  vector<int64_t> tsVec;
  uint64_t tuplePos = 0;
 protected:
  void pipeLineInit(void);
  uint32_t delayTime = 0;
 public:
  void setInStream(MemAddresserPtr _ins) {
    inStream = _ins;
    size_t tupleCnt = inStream->numberOfBitsAllocated / 32;
    printf("tupleCnt=%d\r\n", tupleCnt);
    tsVec = vector<int64_t>(tupleCnt);
  }
  void setDelayTime(uint64_t dt) {
    size_t i;
    for (i = 0; i < tsVec.size(); i++) {
      tsVec[i] = i * dt;
      //printf("%lx\r\n", tsVec[i]);
    }
    printf("allow max t=%ld us\r\n", dt * tsVec.size() / 1000);
    delayTime = dt;
  }
  MemAddresserPtr inStream;

  ~Tcomp32LoadStage() {}
  Tcomp32LoadStage(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      Tcomp32StageBase(cpu, inputQueue, outputQueue) {

  }
  Tcomp32LoadStage(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      Tcomp32StageBase(cpu, _hasNextStage, prev, _ownQueSize) {

  }
  void pipeLineFunction();

};
typedef std::shared_ptr<Tcomp32LoadStage> Tcomp32LoadStagePtr;
/*class:Tcomp32RemapStage
description: The pipeline stage of remaping data
date:202001112
*/
class Tcomp32RemapStage : public Tcomp32StageBase {
 public:
  //MemAddresserPtr inStream;
  ~Tcomp32RemapStage() {}
  Tcomp32RemapStage(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      Tcomp32StageBase(cpu, inputQueue, outputQueue) {

  }
  Tcomp32RemapStage(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      Tcomp32StageBase(cpu, _hasNextStage, prev, _ownQueSize) {

  }

  void pipeLineFunction();

};
typedef std::shared_ptr<Tcomp32RemapStage> Tcomp32RemapStagePtr;
/*class:Tcomp32WriteStage
description: The pipeline stage of writing data
date:202001112
*/
class Tcomp32WriteStage : public Tcomp32StageBase {
 public:
  MemAddresserPtr outStream;
  ~Tcomp32WriteStage() {}
  Tcomp32WriteStage(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      Tcomp32StageBase(cpu, inputQueue, outputQueue) {

  }
  Tcomp32WriteStage(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      Tcomp32StageBase(cpu, _hasNextStage, prev, _ownQueSize) {

  }
  void pipeLineFunction();
  double getIpm() {
    return getinLineIpm(loopMax * 2); //unaligned mem, should*2
  }
};
typedef std::shared_ptr<Tcomp32WriteStage> Tcomp32WriteStagePtr;
/*class:Tcomp32PipeLine
description: The whole pipeline for tcomp32
date:202001210
*/
class Tcomp32PipeLine : public AbstractPipeLine {
 private:
  /* data */
  ADB::length_t safetySize, stopPOS;
  Tcomp32LoadStagePtr s0;
  Tcomp32RemapStagePtr s1;
  Tcomp32WriteStagePtr s2;
  QueueStagePtr passArg01, passArg12;
 public:
  MemAddresserPtr inStream, outStream;
  Tcomp32PipeLine(/* args */);
  void setPar(uint32_t delay) {
    s0->setDelayTime(delay);
  }
  //void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void execute();
  ~Tcomp32PipeLine();
  Tcomp32PipeLine(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
};
typedef std::shared_ptr<Tcomp32PipeLine> Tcomp32PipeLinePtr;
}

#endif