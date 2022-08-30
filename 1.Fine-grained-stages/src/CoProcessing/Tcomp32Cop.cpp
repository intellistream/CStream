//
// Created by tony on 10/04/22.
//

#include <CoProcessing/Tcomp32Cop.h>
using namespace ADB;
void Tcomp32Step::threadMain() {
  //cout<<"enter thread\r\n";
  // return;
  pipeLineInit();
  while (1) {
    // waitForSource();
    //
    while (!inputEmpty()) {
      pipeLineRunMyTurn();
    }
    if (inputEmpty()) {// cout<<"empty"<<endl;
      if (!cmdQueue->empty()) {
        int ts;
        cmdQueue->pop(ts);
        ackQueue->push(2);
        return;
      }
      //waitForSource();
    }

    //  waitData();
  }

}
//s2
void Tcomp32S2::pipeLineInit() {
  //queue, buffer, and mem addresser
  //inQueue= make_shared<boost::lockfree::queue<Tcomp32EncodeInfo>>(queSize);
  outBuf = std::shared_ptr<ADB::memCeil_t>(new ADB::memCeil_t[outLen],
                                           [](ADB::memCeil_t *p) {
                                             delete[] p;
                                           });
  outStream = make_shared<MemAddresser>(outBuf.get(), outLen);
  outBits = 0;

}
void Tcomp32S2::pipeLineRunMyTurn() {

  Tcomp32EncodeInfo info;
  bool tryPop;
  tryPop = inQueue->pop(info);
  if (!tryPop) {
    return;
  }
  outStream->writeValue<uint64_t>(info.value, info.bits);

  outQueue->push(1);
  //cout<<"s2:"+to_string(info.value)+","+"bits"+ to_string(info.bits)+"\r\n";

}

// s1
void Tcomp32S1::pipeLineInit() {
  //inQueue= make_shared<INTELLI::SPSCQueue<uint32_t>>(queSize);
}

void Tcomp32S1::pipeLineRunMyTurn() {
  //cout<<"S1 my turn for"+ to_string(cpuBind)+",range "+ to_string(distMeStart)+"-"+ to_string(distMeEnd)+"("+ to_string(distCnt)+")\r\n"<<endl;

  uint32_t info;
  bool tryPop;
  tryPop = inQueue->pop(info);
  if (!tryPop) {
    return;
  }
  //info=0;
  size_t bits;
  if (info == 0) {
    bits = 1;
  } else {
    bits = 32 - __builtin_clz(info);
  }

  uint64_t remapValue = (info << 5) | (bits - 1);
  uint64_t remapLength = bits + 5;
  Tcomp32EncodeInfo encode(remapValue, remapLength);
  bool isOutBig = shouldOutputBig();
  if (isOutBig) {
    outQueueBig->push(encode);
  } else {
    outQueueLittle->push(encode);
  }
//cout<<"s1:"+to_string(info)+","+"bits"+ to_string(bits)+", pop st"+ to_string(tryPop)+"\r\n";
}
void Tcomp32S1::pipeLineRunNotMyTurn() {
  /*uint32_t info = inQueue->front()[0];
  assert(info==info);*/

}

//s0
void Tcomp32S0::pipeLineInit() {
  // cout<<to_string(queSize)<<endl;
  //inQueue= make_shared<INTELLI::SPSCQueue<vector<uint32_t>>>(100);
//cout<<"s0 at core "+ to_string(cpuBind)+",range "+ to_string(distMeStart)+"-"+ to_string(distMeEnd)+"("+ to_string(distMax)+")"<<endl;
}

void Tcomp32S0::pipeLineRunMyTurn() {
  vector<uint32_t> info;
  bool tryPop;
  tryPop = inQueue->pop(info);
  if (!tryPop) {
    return;
  }
  for (size_t j = 0; j < info.size(); j++) {
    bool isOutBig = shouldOutputBig();
    if (isOutBig) {
      outQueueBig->push(info[j]);
    } else {
      outQueueLittle->push(info[j]);
    }
  }
}
//co-processing
void Tcomp32Cop::initThreads(size_t bigCoreWeight, size_t littleCoreWeight, size_t bigCores, size_t littleCores) {

  // reverse order init steps
  cores = bigCores + littleCores;
  distCnt = 0;
  distMax = bigCoreWeight + littleCoreWeight;
  distLittleMax = littleCoreWeight;

  //initBar=std::make_shared<std::barrier<>>(cores*3+1);
  s0Threads = vector<Tcomp32S0Ptr>(cores);
  s1Threads = vector<Tcomp32S1Ptr>(cores);
  s2Threads = vector<Tcomp32S2Ptr>(cores);

  s2LittleQueue = make_shared<boost::lockfree::stack<Tcomp32EncodeInfo>>(ques);
  s2BigQueue = make_shared<boost::lockfree::stack<Tcomp32EncodeInfo>>(ques);

  s1LittleQueue = make_shared<boost::lockfree::stack<uint32_t>>(ques);
  s1BigQueue = make_shared<boost::lockfree::stack<uint32_t>>(ques);

  s0LittleQueue = make_shared<boost::lockfree::stack<vector<uint32_t>>>(ques);
  s0BigQueue = make_shared<boost::lockfree::stack<vector<uint32_t>>>(ques);
  processedQueue = make_shared<boost::lockfree::stack<char>>(ques);
  for (size_t i = 0; i < cores; i++) {
    s2Threads[i] = make_shared<Tcomp32S2>();
    s2Threads[i]->setOutLen(outBufLen);
    s1Threads[i] = make_shared<Tcomp32S1>();
    s0Threads[i] = make_shared<Tcomp32S0>();
  }
  for (size_t i = 0; i < littleCores; i++) {
    s2Threads[i]->init(LITTLE_CORE_BASE + i, ques, initBar);
    s2Threads[i]->setDistRegion(bigCoreWeight, littleCoreWeight);
    s2Threads[i]->setOutLen(outBufLen);
    s2Threads[i]->setQueue(s2LittleQueue, processedQueue);

    s1Threads[i]->init(LITTLE_CORE_BASE + i, ques, initBar);
    s1Threads[i]->setDistRegion(bigCoreWeight, littleCoreWeight);
    s1Threads[i]->setQueue(s1LittleQueue, s2BigQueue, s2LittleQueue);

    s0Threads[i]->init(LITTLE_CORE_BASE + i, ques, initBar);
    s0Threads[i]->setDistRegion(bigCoreWeight, littleCoreWeight);
    s0Threads[i]->setQueue(s0LittleQueue, s1BigQueue, s1LittleQueue);
    //  s0Threads[i]->pipeLineInit();
  }
  //big cores
  for (size_t j = 0; j < bigCores; j++) {
    size_t i = littleCores + j;
    s2Threads[i]->init(BIG_CORE_BASE + j, ques, initBar);
    s2Threads[i]->setDistRegion(bigCoreWeight, littleCoreWeight);
    s2Threads[i]->setOutLen(outBufLen);
    s2Threads[i]->setQueue(s2BigQueue, processedQueue);

    s1Threads[i]->init(BIG_CORE_BASE + j, ques, initBar);
    s1Threads[i]->setDistRegion(bigCoreWeight, littleCoreWeight);
    s1Threads[i]->setQueue(s1BigQueue, s2BigQueue, s2LittleQueue);

    s0Threads[i]->init(BIG_CORE_BASE + j, ques, initBar);
    s0Threads[i]->setDistRegion(bigCoreWeight, littleCoreWeight);
    s0Threads[i]->setQueue(s0BigQueue, s1BigQueue, s1LittleQueue);
  }
}
void Tcomp32Cop::run() {
// AbstractThread::start();
  for (size_t i = 0; i < cores; i++) {
    s0Threads[i]->start();
    s1Threads[i]->start();
    s2Threads[i]->start();
  }
  standAloneWaiting = false;
  //
//  initBar->arrive_and_wait();
}
void Tcomp32Cop::threadMain() {
  waitForFinish();

}
void Tcomp32Cop::stop() {
  //
  //cout<<to_string(this->processedQueue->)
  /*while (tupleCnt<tupleMax)
  {
    if (!processedQueue->empty())
    {
      char ack;
      processedQueue->pop(ack);
      tupleCnt++;
    //  cout<<to_string(tupleCnt)<<endl;
    }
  }*/
  //AbstractThread::join();
  if (standAloneWaiting) {
    join();
  }
  for (size_t i = 0; i < cores; i++) {
    s0Threads[i]->stop();
    s1Threads[i]->stop();
    s2Threads[i]->stop();
  }
  for (size_t i = 0; i < cores; i++) {
    s0Threads[i]->waitAck();
    s1Threads[i]->waitAck();
    s2Threads[i]->waitAck();
  }
  for (size_t i = 0; i < cores; i++) {
    s0Threads[i]->join();
    s1Threads[i]->join();
    s2Threads[i]->join();
  }
  // this->join();

}
size_t Tcomp32Cop::outPutLen() {
  size_t ru = 0;
  for (size_t i = 0; i < cores; i++) {
    ru += s2Threads[i]->getOutLen();
  }
  return ru;
}
void Tcomp32Cop::inputQueue(vector<uint32_t> in) {
  if (distCnt >= distLittleMax) {
    s0BigQueue->push(in);
  } else {
    s0LittleQueue->push(in);
  }
  distCnt++;
  if (distCnt >= distMax) {
    distCnt = 0;
  }
}