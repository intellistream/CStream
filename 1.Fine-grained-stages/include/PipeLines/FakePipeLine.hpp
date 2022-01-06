#ifndef ADB_INCLUDE_PIPELINES_FAKEPIPELINE_HPP_
#define ADB_INCLUDE_PIPELINES_FAKEPIPELINE_HPP_
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <Utils/MemAddresser.hpp>
#include <CommonData/CommonData.hpp>
#include <PipeLines/Tcomp32PipeLine.hpp>
using namespace std;
namespace ADB {

typedef std::shared_ptr<Tcomp32StageBase> Tcomp32StageBasePtr;
/*class:IdleLoopStage
description: The pipeline stage, which doses nothing but count idle loops
date:202001013
*/
class IdleLoopStage : public Tcomp32StageBase {
 private:
  uint32_t inIdleCnt = 1;
  uint32_t inRu;
 public:
  MemAddresserPtr outStream;
  ~IdleLoopStage() {}
  IdleLoopStage(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      Tcomp32StageBase(cpu, inputQueue, outputQueue) {

  }

  IdleLoopStage(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      Tcomp32StageBase(cpu, _hasNextStage, prev, _ownQueSize) {

  }
  //void pipeLineFunction();
  double getIpm() {
    return getinLineIpm(loopMax);
  }
  void pipeLineFunction() {

    Tcomp32StageBase::pipeLineFunction();
    inRu = 0;
    register uint32_t i;
    for (i = 0; i < inIdleCnt; i++) {
      inRu += i;
    }

  }
  void setIdle(uint32_t ic) {
    inIdleCnt = ic;
  }
};
typedef std::shared_ptr<IdleLoopStage> IdleLoopStagePtr;
/*class:FakePipeLine
description: The Fake pipe line does nothing but passing args from stage to stage
date:20211111
*/
class FakePipeLine : public AbstractPipeLine {
 private:
  /* data */
  ADB::length_t safetySize, stopPOS;
  IdleLoopStagePtr s0, s1;
  QueueStagePtr passArg01, passArg12;

 public:
  MemAddresserPtr inStream, outStream;
  FakePipeLine(/* args */);
  //void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void execute();
  ~FakePipeLine();
  FakePipeLine(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void setIdleCnt(uint32_t cnt0, uint32_t cnt1) {
    s0->setIdle(cnt0);
    s1->setIdle(cnt1);
  }
};
typedef std::shared_ptr<FakePipeLine> FakePipeLinePtr;
}

#endif