#include <PipeLines/Tcomp32PipeLine2S.hpp>
//load, stage1
//remap, stage22s
static uint32_t ppp_remap(uint32_t a) {
  if (a == 0) {
    return 1;
  }
  return 32 - __builtin_clz(a);
}
void Tcomp32LMStage::pipeLineFunction() {

  uint32_t value = inStream->readAlignedValue<uint32_t>();
  // printf("read %d %d-%d\r\n",value,loopCnt,loopMax);
  uint32_t n = ppp_remap(value);
  midArg.remapValue = (value << 5) | (n - 1);
  midArg.remapLength = n + 5;
  //loopCnt += 4;
  Tcomp32StageBase::pipeLineFunction();

}
Tcomp32PipeLine2S::Tcomp32PipeLine2S() {
}

Tcomp32PipeLine2S::~Tcomp32PipeLine2S() {

}
Tcomp32PipeLine2S::Tcomp32PipeLine2S(ADB::length_t inS,
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

  s0 = make_shared<Tcomp32LMStage>(4, nullptr, passArg01);
 
  s1 = make_shared<Tcomp32WriteStage>(5, passArg01, nullptr);*/
  s0 = make_shared<Tcomp32LMStage>(0, true, nullptr, stopPOS / 4);
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
void Tcomp32PipeLine2S::execute() {

  /*s0->start();
  s1->start();
  s2->start();
  s0->join();
  s1->join();
  s2->join();*/
  AbstractPipeLine::execute();

}