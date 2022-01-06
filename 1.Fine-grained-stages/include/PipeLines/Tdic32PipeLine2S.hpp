#ifndef ADB_INCLUDE_PIPELINES_TDIC32PIPELINE2S_HPP_
#define ADB_INCLUDE_PIPELINES_TDIC32PIPELINE2S_HPP_
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <Utils/MemAddresser.hpp>
#include <CommonData/CommonData.hpp>
#include <PipeLines/Tcomp32PipeLine.hpp>
using namespace std;
namespace ADB {
#define INVALID_OFFSET 0XFFFFFFFF
typedef  struct { /*uint32_t idex; */uint32_t word; } tdic32_hash_entry_t;

#define TDIC_COMPRESS_HASH_BITS 11
#define TDIC_COMPRESS_HASH_ENTRIES (1 << TDIC_COMPRESS_HASH_BITS)
#define TDIC_COMPRESS_HASH_MULTIPLY 2654435761U
#define TDIC_COMPRESS_HASH_SHIFT (32 - TDIC_COMPRESS_HASH_BITS)
static inline uint32_t tdic32_hash(uint32_t x) { return (x * 2654435761U) >> (32 - TDIC_COMPRESS_HASH_BITS); }
static inline void tdic32_initTable(tdic32_hash_entry_t *tb,uint32_t tLen)
{
    uint32_t i;
    for(i=0;i<tLen;i++)
    {
        tb[i].word=INVALID_OFFSET;
    }
    tb[tdic32_hash(INVALID_OFFSET)].word=0;
}
/*class:Tdic32LMStage
description: The pipeline stage of loading 32-bit data and remap it

date:20211121
*/

class Tdic32LMStage : public Tcomp32StageBase {
 private:
 tdic32_hash_entry_t tb[TDIC_COMPRESS_HASH_ENTRIES];
 public:

  MemAddresserPtr inStream;
  ~Tdic32LMStage() {

  }
  Tdic32LMStage(length_t cpu, QueueStagePtr inputQueue, QueueStagePtr outputQueue) :
      Tcomp32StageBase(cpu, inputQueue, outputQueue) {
        tdic32_initTable(tb,TDIC_COMPRESS_HASH_ENTRIES);
  }
  Tdic32LMStage(length_t cpu, bool _hasNextStage, AbstractPipeLineStagePtr prev, length_t _ownQueSize) :
      Tcomp32StageBase(cpu, _hasNextStage, prev, _ownQueSize) {
         tdic32_initTable(tb,TDIC_COMPRESS_HASH_ENTRIES);
  }
  void pipeLineFunction();
  double getIpm() {
    return getinLineIpm(loopMax * 2); //another one for hash table
  }
};
typedef std::shared_ptr<Tdic32LMStage> Tdic32LMStagePtr;

/*class:Tdic32PipeLine
description: The whole pipeline for tdic32, IN 2 stages
date:202001121
*/
class Tdic32PipeLine2S : public AbstractPipeLine {
 private:
  /* data */
  ADB::length_t safetySize, stopPOS;
  Tdic32LMStagePtr s0;
  Tcomp32WriteStagePtr s1; //same component of tcomp32
  QueueStagePtr passArg01, passArg12;
 public:
  MemAddresserPtr inStream, outStream;
  Tdic32PipeLine2S(/* args */);
  //void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void execute();
  ~Tdic32PipeLine2S();
  Tdic32PipeLine2S(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
};
typedef std::shared_ptr<Tdic32PipeLine2S> Tdic32PipeLine2SPtr;
}

#endif