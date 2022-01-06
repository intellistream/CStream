#ifndef ADB_INCLUDE_PIPELINES_TCOMP32PIPELINE2S_HPP_
#define ADB_INCLUDE_PIPELINES_TCOMP32PIPELINE2S_HPP_
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <Utils/MemAddresser.hpp>
#include <CommonData/CommonData.hpp>
#include <PipeLines/Tcomp32PipeLine.hpp>
using namespace std;
namespace ADB {

/*class:Tcomp32LMStage
description: The pipeline stage of loading 32-bit data and remap it

date:202001112
*/
class Tcomp32LMStage : public Tcomp32StageBase {
 public:

  MemAddresserPtr inStream;
  ~Tcomp32LMStage() {

  }
  Tcomp32LMStage(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      Tcomp32StageBase(cpu, inputQueue, outputQueue) {

  }
  Tcomp32LMStage(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      Tcomp32StageBase(cpu, _hasNextStage, prev, _ownQueSize) {

  }
  void pipeLineFunction();

};
typedef std::shared_ptr<Tcomp32LMStage> Tcomp32LMStagePtr;

/*class:Tcomp32PipeLine
description: The whole pipeline for tcomp32, IN 2 stages
date:202001027
*/
class Tcomp32PipeLine2S : public AbstractPipeLine {
 private:
  /* data */
  ADB::length_t safetySize, stopPOS;
  Tcomp32LMStagePtr s0;
  Tcomp32WriteStagePtr s1;
  QueueStagePtr passArg01, passArg12;
 public:
  MemAddresserPtr inStream, outStream;
  Tcomp32PipeLine2S(/* args */);
  //void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void execute();
  ~Tcomp32PipeLine2S();
  Tcomp32PipeLine2S(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
};
typedef std::shared_ptr<Tcomp32PipeLine2S> Tcomp32PipeLine2SPtr;
}

#endif