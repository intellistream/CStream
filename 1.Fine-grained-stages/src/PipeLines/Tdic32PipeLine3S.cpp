#include <PipeLines/Tdic32PipeLine3S.hpp>
using namespace ADB;
void Tdic32FeedStage::pipeLineFunction()
{
  uint32_t i;
  StageParseArgs targ;
  printf("%d\r\n",tupleLenU32);
  for(i=0;i<tupleLenU32-1;i++)
  {
    targ.remapValue=inStream->readAlignedValue<uint32_t>();
    printf("pipe func,%d\r\n",i);
  }
  midArg.remapValue=5;
  //midArg.remapValue=inStream->readAlignedValue<uint32_t>();
  //usleep(minSleep);
 // midArg.remapValue = inStream->readAlignedValue<uint32_t>();

  loopCnt += tupleLenU32;
 // Tcomp32StageBase::pipeLineFunction();

 // Tcomp32StageBase::pipeLineFunction();
}
void Tdic32MapStage::pipeLineFunction() {

  uint32_t num =midArg.remapValue;
   uint32_t i0 = tdic32_hash(num);
   tdic32_hash_entry_t ru = tb[i0];
   if(ru.word==num) //found
   {
        midArg.remapValue =(i0<<1)|1;
        midArg.remapLength = TDIC_COMPRESS_HASH_BITS+ 1;
   }
   else
   {
        midArg.remapValue =num;
        midArg.remapValue=(midArg.remapValue<<1)|0;
        midArg.remapLength =33;
        tb[i0].word=num;
   }
  Tcomp32StageBase::pipeLineFunction();

}

Tdic32PipeLine3S::Tdic32PipeLine3S() {
}

Tdic32PipeLine3S::~Tdic32PipeLine3S() {

}
Tdic32PipeLine3S::Tdic32PipeLine3S(ADB::length_t inS,
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

  s0 = make_shared<Tdic32MapStage>(4, nullptr, passArg01);
 
  s1 = make_shared<Tdic32WriteStage>(5, passArg01, nullptr);*/
  //stopPOS=400;
  s0 = make_shared<Tcomp32LoadStage>(0, true, nullptr, stopPOS / 4);
  s1 = make_shared<Tdic32MapStage>(1, true, s0, stopPOS / 4);
  s2 = make_shared<Tcomp32WriteStage>(2, false, s1, stopPOS / 4);
  s0->setName("feed");

  s1->setName("remap");
  s2->setName("write");
  s0->setLoop(stopPOS / 4);
  s1->setLoop(stopPOS / 4);
  s2->setLoop(stopPOS / 4);
  s0->setInStream(this->inStream);
 
  s2->outStream = this->outStream;
  stages.push_back(s0);
  stages.push_back(s1);
  stages.push_back(s2);
  setUpMeter();

}
void Tdic32PipeLine3S::execute() {

  AbstractPipeLine::execute();

}
Tdic32PipeLineOnlyFeed::Tdic32PipeLineOnlyFeed()
{

}
Tdic32PipeLineOnlyFeed::~Tdic32PipeLineOnlyFeed()
{

}
Tdic32PipeLineOnlyFeed::Tdic32PipeLineOnlyFeed(ADB::length_t inS,
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
  
  s0->setName("load ");
 
  s0->setLoop(stopPOS / 16);
  s0->setInStream(this->inStream);
  //s0->inStream = this->inStream;
  stages.push_back(s0);
  
  setUpMeter();

}

void Tdic32PipeLineOnlyFeed::execute() {

  AbstractPipeLine::execute();

}