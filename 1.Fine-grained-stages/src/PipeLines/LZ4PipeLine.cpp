#include <PipeLines/LZ4PipeLine.hpp>
//load, stage1

void LZ4LoadStage::pipeLineFunction() {

  uint32_t value = inStream->readAlignedValue<uint32_t>(&inStream->data[privateArg->src_ptr]);
  lz4_hash_entry_t hashRu = privateArg->updateHashTable(privateArg->src_ptr, value);
  uint32_t distance = privateArg->src_ptr - hashRu.offset;
  uint32_t matchLen;
  if (hashRu.offset != INVALID_OFFSET && distance < 0x10000 && distance > 3 && hashRu.word == value) //valid
  {
    matchLen = LZ4ExpandSearchingComponent::count_match(inStream->getData(),
                                                        hashRu.offset,
                                                        privateArg->src_ptr,
                                                        privateArg->max_ptr);

  } else {
    matchLen = 0;
  }
  if (matchLen < 4) {
    matchLen = 0;
  }

  midArg.remapLength = matchLen;
  midArg.remapValue = distance;
  //loopCnt += 4;

  if (matchLen) {
    privateArg->src_ptr += matchLen;
    privateArg->literal_head = privateArg->src_ptr;
    inStream->readOffset += matchLen << 3;
  } else {
    privateArg->src_ptr += 1;
    inStream->readOffset += 8;
  }

}
//write, last
void LZ4WriteStage::pipeLineFunction() {

  matchLen = midArg.remapLength;
  distance = midArg.remapValue;
  if (privateArg->src_ptr >= privateArg->max_ptr - 3) {
    privateArg->src_ptr += 4;
    privateArg->dst_ptr += LZ4WriteSequenceComponent::copy_sequence(outStream->getData(),
                                                                    privateArg->dst_ptr,
                                                                    inStream->getData(),
                                                                    privateArg->literal_head,
                                                                    privateArg->max_ptr,
                                                                    0,
                                                                    0);
    // printf("to the end%d\r\n",privateArg->src_ptr);
    outStream->numberOfBitsUsed = privateArg->dst_ptr << 3;
    // exit(0);
    return;
  }
  if (matchLen) {
    privateArg->dst_ptr += LZ4WriteSequenceComponent::copy_sequence(outStream->getData(),
                                                                    privateArg->dst_ptr,
                                                                    inStream->getData(),
                                                                    privateArg->literal_head,
                                                                    privateArg->src_ptr,
                                                                    distance,
                                                                    matchLen);
    privateArg->src_ptr += matchLen;
    privateArg->literal_head = privateArg->src_ptr;
    outStream->numberOfBitsUsed = privateArg->dst_ptr << 3;
  } else {
    /* code */
    privateArg->src_ptr += 1;
  }

  LZ4StageBase::pipeLineFunction();
}

LZ4PipeLine::LZ4PipeLine() {
}

LZ4PipeLine::~LZ4PipeLine() {

}
LZ4PipeLine::LZ4PipeLine(ADB::length_t inS,
                         ADB::length_t outS,
                         ADB::length_t _safetySize,
                         ADB::memPtr inP,
                         ADB::memPtr outP) {
  inStream = make_shared<MemAddresser>(inP, inS);
  inStream2 = make_shared<MemAddresser>(inP, inS);
  outStream = make_shared<MemAddresser>(outP, outS);
  safetySize = _safetySize;
  stopPOS = inS;
  //prepare the queues

  //prepare stages
  /*QueueStagePtr passArg01 = make_shared < INTELLI::SPSCQueue < StageParseArgs >> (stopPOS);
  QueueStagePtr passArg12 = make_shared < INTELLI::SPSCQueue < StageParseArgs >> (stopPOS);

  s0 = make_shared<LZ4LoadStage>(4, nullptr, passArg01);
  s1 = make_shared<LZ4WriteStage>(2, passArg01, nullptr);*/
  s0 = make_shared<LZ4LoadStage>(0, true, nullptr, stopPOS);
  s1 = make_shared<LZ4WriteStage>(1, false, s0, 0);
  s0->setName("load&match");
  s1->setName("writeToken");
  s0->setLoop(stopPOS);
  s1->setLoop(stopPOS);
  s0->inStream = this->inStream;
  s1->inStream = this->inStream2;
  s1->outStream = this->outStream;
  stages.push_back(s0);
  stages.push_back(s1);
  setUpMeter();
}
void LZ4PipeLine::execute() {

  /*s0->start();
  s1->start();
  s2->start();
  s0->join();
  s1->join();
  s2->join();*/
  AbstractPipeLine::execute();

}