#ifndef ADB_INCLUDE_PIPELINES_TDIC32PIPELINE3S_HPP_
#define ADB_INCLUDE_PIPELINES_TDIC32PIPELINE3S_HPP_
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <Utils/MemAddresser.hpp>
#include <CommonData/CommonData.hpp>
#include <PipeLines/Tdic32PipeLine2S.hpp>
using namespace std;
using namespace ADB;
namespace ADB {

/*class:Tdic32FeedStage
description: The pipeline stage of feed tuples

date:20211207
*/

class Tdic32FeedStage : public Tcomp32StageBase {
 private:
  uint32_t tupleLenU32; // in 32-bit word
  //in us
  uint32_t maxSleep = 1000;
  uint32_t minSleep = 10;
 public:
  MemAddresserPtr inStream;

  ~Tdic32FeedStage() {

  }
  Tdic32FeedStage(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      Tcomp32StageBase(cpu, inputQueue, outputQueue) {
    //tdic32_initTable(tb,TDIC_COMPRESS_HASH_ENTRIES);
  }
  Tdic32FeedStage(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      Tcomp32StageBase(cpu, _hasNextStage, prev, _ownQueSize) {
    //  tdic32_initTable(tb,TDIC_COMPRESS_HASH_ENTRIES);
  }
  void setSleep(uint32_t mins, uint32_t maxs) {
    minSleep = mins;
    maxSleep = maxs;
  }
  void setTupleLen(uint32_t tl) {
    tupleLenU32 = tl;

  }
  void pipeLineFunction();
  double getIpm() {
    return getinLineIpm(loopMax); //another one for hash table
  }
};
typedef std::shared_ptr<Tdic32FeedStage> Tdic32FeedStagePtr;
/*class:Tdic32MapStage
description: The pipeline stage of and remaping it

date:20211207
*/

class Tdic32MapStage : public Tcomp32StageBase {
 private:
  tdic32_hash_entry_t tb[TDIC_COMPRESS_HASH_ENTRIES];
 public:

  MemAddresserPtr inStream;
  ~Tdic32MapStage() {

  }
  Tdic32MapStage(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      Tcomp32StageBase(cpu, inputQueue, outputQueue) {
    tdic32_initTable(tb, TDIC_COMPRESS_HASH_ENTRIES);
  }
  Tdic32MapStage(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      Tcomp32StageBase(cpu, _hasNextStage, prev, _ownQueSize) {
    tdic32_initTable(tb, TDIC_COMPRESS_HASH_ENTRIES);
  }
  void pipeLineFunction();
  double getIpm() {
    return getinLineIpm(loopMax * 2); //another one for hash table
  }
};
typedef std::shared_ptr<Tdic32MapStage> Tdic32MapStagePtr;

/*class:Tdic32PipeLine3s
description: The whole pipeline for tdic32, IN 3 stages including the data feeding
date:20211207
*/
class Tdic32PipeLine3S : public AbstractPipeLine {
 private:
  /* data */
  ADB::length_t safetySize, stopPOS;
  Tcomp32LoadStagePtr s0;
  Tdic32MapStagePtr s1;
  Tcomp32WriteStagePtr s2; //same component of tcomp32
  QueueStagePtr passArg01, passArg12;
 public:
  MemAddresserPtr inStream, outStream;
  Tdic32PipeLine3S(/* args */);
  //void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void execute();
  void setPar(uint32_t delay) {
    s0->setDelayTime(delay);
  }
  ~Tdic32PipeLine3S();
  Tdic32PipeLine3S(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
};
typedef std::shared_ptr<Tdic32PipeLine3S> Tdic32PipeLine3SPtr;

class Tdic32PipeLineOnlyFeed : public AbstractPipeLine {
 private:
  /* data */
  ADB::length_t safetySize, stopPOS;
  Tcomp32LoadStagePtr s0;

  QueueStagePtr passArg01, passArg12;
 public:
  MemAddresserPtr inStream, outStream;

  //void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void execute();
  void setPar(uint32_t delay) {
    s0->setDelayTime(delay);
  }
  /*[
    s0->setSleep(mins,maxs);
    s0->setLoop(stopPOS / (4*tupleLen));
    s0->setTupleLen(tupleLen);
  ]*/
  ~Tdic32PipeLineOnlyFeed();
  Tdic32PipeLineOnlyFeed();
  Tdic32PipeLineOnlyFeed(ADB::length_t inS,
                         ADB::length_t outS,
                         ADB::length_t safetySize,
                         ADB::memPtr inP,
                         ADB::memPtr outP);
};
typedef std::shared_ptr<Tdic32PipeLineOnlyFeed> Tdic32PipeLineOnlyFeedPtr;
}

#endif