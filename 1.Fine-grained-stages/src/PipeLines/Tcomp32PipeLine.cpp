#include <PipeLines/Tcomp32PipeLine.hpp>
//load, stage1
void Tcomp32LoadStage::pipeLineInit()
{
  StageParseArgs targ;
 
   /*for(int i=0;i<4;i++)
    {
      targ.remapValue=inStream->readAlignedValue<uint32_t>();
      outputQueue->push(targ);
    }*/
    targ.remapValue=inStream->readAlignedValue<uint32_t>();
      outputQueue->push(targ);
   //midArg.remapValue = inStream->readAlignedValue<uint32_t>();
  loopCnt++;
  tuplePos=1;
   clk.reset(); 
  timeBase=clk.getNs();
  printf("init load at %ld\r\n",timeBase);
 

}

void Tcomp32LoadStage::pipeLineFunction() {

  int64_t timeStampStream=tsVec[tuplePos];
  

 int64_t timeStampSys=clk.getNs()-timeBase;
 
 while (timeStampSys<timeStampStream)
  {
    std::this_thread::sleep_for(std::chrono::nanoseconds(delayTime));
     timeStampSys=clk.getNs()-timeBase;
  }
  
  
 
  tuplePos++;
   // std::this_thread::sleep_for(std::chrono::microseconds(delayTime/1000));
// printf("should push%lx\r\n",timeStampStream);
  StageParseArgs targ;
  /*  for(int i=0;i<3;i++)
    {
      targ.remapValue=inStream->readAlignedValue<uint32_t>();
      outputQueue->push(targ);
    }*/
   midArg.remapValue = inStream->readAlignedValue<uint32_t>();
  loopCnt++;
 
 /*}*/


}
//the sleep version

//remap, stage2
static uint32_t ppp_remap(uint32_t a) {
  if (a == 0) {
    return 1;
  }
  return 32 - __builtin_clz(a);
}
void Tcomp32RemapStage::pipeLineFunction() {
  /*while (!inputQueue->empty()) {//process the remaining data streams after source stops.
    midArg = *inputQueue->front();
    inputQueue->pop();
    length_t value = midArg.remapValue;
    uint32_t n = ppp_remap(value);
    midArg.remapValue = (value << 5) | (n - 1);
    midArg.remapLength = n + 5;
    Tcomp32StageBase::pipeLineFunction();
    outputQueue->push(midArg);
  }*/
  length_t value = midArg.remapValue;
  uint32_t n = ppp_remap(value);
  midArg.remapValue = (value << 5) | (n - 1);
  midArg.remapLength = n + 5;
  Tcomp32StageBase::pipeLineFunction();
}
//write, last
void Tcomp32WriteStage::pipeLineFunction() {
  /*while (!inputQueue->empty()) {
    midArg = *inputQueue->front();
    inputQueue->pop();
    outStream->writeValue<uint64_t>(midArg.remapValue, midArg.remapLength);
    Tcomp32StageBase::pipeLineFunction();
  }*/
  outStream->writeValue<uint64_t>(midArg.remapValue, midArg.remapLength);
  Tcomp32StageBase::pipeLineFunction();
}

Tcomp32PipeLine::Tcomp32PipeLine() {
}

Tcomp32PipeLine::~Tcomp32PipeLine() {

}
Tcomp32PipeLine::Tcomp32PipeLine(ADB::length_t inS,
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
  /*QueueStagePtr passArg01 = make_shared < rigtorp::SPSCQueue < StageParseArgs >> (stopPOS/4);
  QueueStagePtr passArg12 = make_shared < rigtorp::SPSCQueue < StageParseArgs >> (stopPOS/4);

  s0 = make_shared<Tcomp32LoadStage>(4, nullptr, passArg01);
  s1 = make_shared<Tcomp32RemapStage>(2, passArg01, passArg12);
  s2 = make_shared<Tcomp32WriteStage>(5, passArg12, nullptr);*/
  s0 = make_shared<Tcomp32LoadStage>(0, true, nullptr, stopPOS / 4);
  s1 = make_shared<Tcomp32RemapStage>(1, true, s0, stopPOS / 4);
  s2 = make_shared<Tcomp32WriteStage>(2, false, s1, 0);
  s0->setName("load ");
  s1->setName("remap");
  s2->setName("write");
  s0->setLoop(stopPOS / 4);
  s1->setLoop(stopPOS / 4);
  s2->setLoop(stopPOS / 4);
  //s0->inStream = this->inStream;
  s0->setInStream(this->inStream);
  s2->outStream = this->outStream;
  stages.push_back(s0);
  stages.push_back(s1);
  stages.push_back(s2);
  setUpMeter();
}
void Tcomp32PipeLine::execute() {

  /*s0->start();
  s1->start();
  s2->start();
  s0->join();
  s1->join();
  s2->join();*/
  AbstractPipeLine::execute();

}