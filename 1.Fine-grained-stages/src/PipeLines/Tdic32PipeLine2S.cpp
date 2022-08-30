#include <PipeLines/Tdic32PipeLine2S.hpp>

void Tdic32LMStage::pipeLineFunction() {

  uint32_t num = inStream->readAlignedValue<uint32_t>();
  uint32_t i0 = tdic32_hash(num);
  tdic32_hash_entry_t ru = tb[i0];
  if (ru.word == num) //found
  {
    midArg.remapValue = (i0 << 1) | 1;
    midArg.remapLength = TDIC_COMPRESS_HASH_BITS + 1;
  } else {
    midArg.remapValue = num;
    midArg.remapValue = (midArg.remapValue << 1) | 0;
    midArg.remapLength = 33;
    tb[i0].word = num;
  }
  Tcomp32StageBase::pipeLineFunction();

}

Tdic32PipeLine2S::Tdic32PipeLine2S() {
}

Tdic32PipeLine2S::~Tdic32PipeLine2S() {

}
Tdic32PipeLine2S::Tdic32PipeLine2S(ADB::length_t inS,
                                   ADB::length_t outS,
                                   ADB::length_t _safetySize,
                                   ADB::memPtr inP,
                                   ADB::memPtr outP) {
  inStream = make_shared<MemAddresser>(inP, inS);
  outStream = make_shared<MemAddresser>(outP, outS);
  safetySize = _safetySize;
  stopPOS = inS;
  //prepare the queues

  //prepare stages
  /*QueueStagePtr passArg01 = make_shared < INTELLI::SPSCQueue < StageParseArgs >> (stopPOS/4);
  QueueStagePtr passArg12 = make_shared < INTELLI::SPSCQueue < StageParseArgs >> (stopPOS/4);

  s0 = make_shared<Tdic32LMStage>(4, nullptr, passArg01);
 
  s1 = make_shared<Tdic32WriteStage>(5, passArg01, nullptr);*/
  s0 = make_shared<Tdic32LMStage>(0, true, nullptr, stopPOS / 4);
  s1 = make_shared<Tcomp32WriteStage>(1, false, s0, stopPOS / 4);
  s0->setName("load+reamp ");

  s1->setName("write");
  s0->setLoop(stopPOS / 4);
  s1->setLoop(stopPOS / 4);

  s0->inStream = this->inStream;
  s1->outStream = this->outStream;
  stages.push_back(s0);
  stages.push_back(s1);
  setUpMeter();

}
void Tdic32PipeLine2S::execute() {

  AbstractPipeLine::execute();

}