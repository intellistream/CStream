//
// Created by tony on 10/04/22.
//

#ifndef _SRC_COPROCESSING_TCOMP32COP_H_
#define _SRC_COPROCESSING_TCOMP32COP_H_
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <Utils/MultiCore/SPSCQueue.hpp>
#include <Utils/MemAddresser.hpp>
#include <CommonData/CommonData.hpp>

#include <MeterHelp.hpp>
#include <vector>
#include <mutex>
#include <boost/lockfree/stack.hpp>
using namespace std;
using namespace ADB;
using namespace INTELLI;
namespace ADB {
class Tcomp32Cop;
/**
 * @class Tcomp32Step
 * @brief The generic step of tcomp32
 */
typedef std::shared_ptr<boost::lockfree::stack<char>> cmdQueuePtr;
class Tcomp32Step : public AbstractThread {
 protected:
  virtual void threadMain();

  cmdQueuePtr cmdQueue = nullptr;
  cmdQueuePtr ackQueue = nullptr;
  // The integer to control distribution
  size_t distMax = 0;
  size_t distCnt = 0;
  size_t distLittleMax = 0;
  size_t tupleCnt = 0;
  size_t tupleCntEnd = 1;
  bool shouldStop = false;
  // Tcomp32S0QueuePtr inQue;
  size_t queSize;
  std::mutex m_mut;
  BarrierPtr initBar = nullptr;


  // std::mutex m_mut;
 public:
  Tcomp32Step() {}
  ~Tcomp32Step() {}
  // void feedQueue(vector<uint32_t>tuple);
  void init(int coreID, size_t inQueSize, BarrierPtr _initBar) {
    cpuBind = coreID;
    queSize = inQueSize;
    initBar = _initBar;
    distCnt = 0;
  }
  void init(int coreID, size_t inQueSize, BarrierPtr _initBar, size_t _tupleCnt) {
    cpuBind = coreID;
    queSize = inQueSize;
    initBar = _initBar;
    tupleCntEnd = _tupleCnt;
    tupleCnt = 0;
    distCnt = 0;
  }
  void setDistRegion(size_t big, size_t little) {
    distMax = big + little;
    distLittleMax = little;
    cmdQueue = make_shared<boost::lockfree::stack<char>>(1);
    ackQueue = make_shared<boost::lockfree::stack<char>>(1);
    pipeLineInit();
  }
  void waitAck() {
    while (ackQueue->empty());
    char ack;
    ackQueue->pop(ack);
  }
  void stop() {
    // while (!m_mut.try_lock());
    cmdQueue->push(1);
  }

  // wether the output should be output to big cores
  bool shouldOutputBig() {
    bool ru = false;
    if (distCnt >= distLittleMax) {
      ru = true;
    }
    distCnt++;
    if (distCnt >= distMax) {
      distCnt = 0;
    }
    return ru;
  }
  virtual void pipeLineRunMyTurn() {}
  // init the pipeline, e.g., local queue
  virtual void pipeLineInit() {
  }
  virtual bool inputEmpty() {
    return true;
  }

};
/**
 * The write output step
 */
class Tcomp32EncodeInfo {
 public:
  uint64_t value;
  uint64_t bits;
  Tcomp32EncodeInfo() {}
  Tcomp32EncodeInfo(uint64_t _val, uint64_t _len) {
    value = _val;
    bits = _len;
  }
  ~Tcomp32EncodeInfo() {}
};
typedef std::shared_ptr<boost::lockfree::stack<Tcomp32EncodeInfo>> Tcomp32S2QueuePtr;
typedef std::shared_ptr<boost::lockfree::stack<uint32_t>> Tcomp32S1QueuePtr;
typedef std::shared_ptr<boost::lockfree::stack<vector<uint32_t>>> Tcomp32S0QueuePtr;
class Tcomp32S2 : public Tcomp32Step {
 protected:
  Tcomp32S2QueuePtr inQueue = nullptr;
  cmdQueuePtr outQueue;
  size_t outLen;
  memPtr_shared outBuf;
  MemAddresserPtr outStream;
  uint64_t outBits = 0;

 public:
  void setOutLen(size_t ol) {
    outLen = ol;
  }
  //execute the pipeline function
  virtual void pipeLineRunMyTurn();

  // init the pipeline, e.g., local queue
  virtual void pipeLineInit();
  //
  void inputQueue(Tcomp32EncodeInfo in) {
    inQueue->push(in);
    /* lock();
     if(updateCnt())
     {//cout<<"s2 input\r\n";

       wakeUpSink();
     }
     unlock();*/
  }
  bool inputEmpty() {
    return inQueue->empty();
  }
  size_t getOutLen() {
    outBits = outStream->numberOfBitsUsed;
    return outBits;
  }
  void setQueue(Tcomp32S2QueuePtr in, cmdQueuePtr out) {
    inQueue = in;
    outQueue = out;
  }

};
typedef std::shared_ptr<Tcomp32S2> Tcomp32S2Ptr;
//S1

class Tcomp32S1 : public Tcomp32Step {
 protected:
  Tcomp32S1QueuePtr inQueue;
  Tcomp32S2QueuePtr outQueueBig, outQueueLittle;
  size_t outLen;
 public:
  //execute the pipeline function
  virtual void pipeLineRunMyTurn();
  virtual void pipeLineRunNotMyTurn();
  // init the pipeline, e.g., local queue
  virtual void pipeLineInit();
  //

  virtual bool inputEmpty() {
    return inQueue->empty();
  }
  void setQueue(Tcomp32S1QueuePtr in, Tcomp32S2QueuePtr ob, Tcomp32S2QueuePtr ol) {
    inQueue = in;
    outQueueBig = ob;
    outQueueLittle = ol;
  }

};
typedef std::shared_ptr<Tcomp32S1> Tcomp32S1Ptr;

class Tcomp32S0 : public Tcomp32Step {
 protected:
  Tcomp32S0QueuePtr inQueue;
  Tcomp32S1QueuePtr outQueueBig, outQueueLittle;
  size_t outLen;
 public:

  //execute the pipeline function
  void pipeLineRunMyTurn();
  // init the pipeline, e.g., local queue
  virtual void pipeLineInit();

  bool inputEmpty() {// cout<<"s0 input empty\r\n"<<endl;
    return inQueue->empty();
  }
  void setQueue(Tcomp32S0QueuePtr in, Tcomp32S1QueuePtr ob, Tcomp32S1QueuePtr ol) {
    inQueue = in;
    outQueueBig = ob;
    outQueueLittle = ol;
  }
};
typedef std::shared_ptr<Tcomp32S0> Tcomp32S0Ptr;
class Tcomp32Cop : public AbstractThread {
 protected:
  size_t ques = 1000;
  size_t outBufLen = 10000;
  size_t cores;
  size_t distCnt = 0;
  size_t distLittleMax = 0;
  size_t distMax = 0;
  size_t tupleCnt = 0;
  size_t tupleMax = 0;
  virtual void threadMain();
  bool standAloneWaiting = false;
 public:
  vector<Tcomp32S2Ptr> s2Threads;
  vector<Tcomp32S1Ptr> s1Threads;
  vector<Tcomp32S0Ptr> s0Threads;
  Tcomp32S2QueuePtr s2LittleQueue, s2BigQueue;
  Tcomp32S1QueuePtr s1LittleQueue, s1BigQueue;
  Tcomp32S0QueuePtr s0LittleQueue, s0BigQueue;
  cmdQueuePtr processedQueue;
  BarrierPtr initBar = nullptr;
  Tcomp32Cop() {}
  ~Tcomp32Cop() {}

  void setQuesAndBuf(size_t _que, size_t bufLen) {
    ques = _que;
    outBufLen = bufLen;
  }
  void initThreads(size_t bigCoreWeight, size_t littleCoreWeight, size_t bigCores, size_t littleCores);
  void inputQueue(vector<uint32_t> in);
  void stop();
  void waitForFinish() {
    while (tupleCnt < tupleMax) {
      while (!processedQueue->empty()) {
        char ack;
        processedQueue->pop(ack);
        tupleCnt++;
        // cout<<to_string(tupleCnt)<<endl;
      }
    }
  }
  void waitForFinishNoBlock() {
    cout << "non-block waiting by using extra thread" << endl;
    start();
    standAloneWaiting = true;

  }
  void run();
  void setTuples(size_t tps) {
    tupleMax = tps;
    tupleCnt = 0;
  }
  void run(size_t tps) {
    setTuples(tps);
    run();
  }
  size_t outPutLen();

};
}

#endif //ALIANCEDB_SRC_COPROCESSING_TCOMP32COP_H_
