#include <PipeLines/FakePipeLine.hpp>

FakePipeLine::FakePipeLine() {
}

FakePipeLine::~FakePipeLine() {

}
FakePipeLine::FakePipeLine(ADB::length_t inS,
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

  s0 = make_shared<IdleLoopStage>(4, nullptr, passArg01);
 
  s1 = make_shared<IdleLoopStage>(5, passArg01, nullptr);*/
  s0 = make_shared<IdleLoopStage>(4, true, nullptr, stopPOS / 4);
  s1 = make_shared<IdleLoopStage>(4, false, s0, stopPOS / 4);
  s0->setName("load+reamp ");

  s1->setName("write");
  s0->setLoop(stopPOS / 4);
  s1->setLoop(stopPOS / 4);
  s0->setIdle(1);
  s1->setIdle(1);
  stages.push_back(s0);
  stages.push_back(s1);
  setUpMeter();

}
void FakePipeLine::execute() {

  /*s0->start();
  s1->start();
  s2->start();
  s0->join();
  s1->join();
  s2->join();*/
  AbstractPipeLine::execute();

}