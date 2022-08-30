//
// Created by tony on 12/04/22.
//

#ifndef ALIANCEDB_INCLUDE_COPROCESSING_TCOMP32COPBA_H_
#define ALIANCEDB_INCLUDE_COPROCESSING_TCOMP32COPBA_H_
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <Utils/MultiCore/SPSCQueue.hpp>
#include <Utils/MemAddresser.hpp>
#include <CommonData/CommonData.hpp>

#include <MeterHelp.hpp>
#include <vector>
#include <mutex>
//#include <boost/lockfree/stack.hpp>
using namespace std;
namespace ADB {
typedef std::shared_ptr<INTELLI::SPSCQueue<uint32_t>> Tcomp32CopBa_s0InQueuePtr;
typedef std::shared_ptr<INTELLI::SPSCQueue<char>> stopQueuePtr;
typedef std::shared_ptr<vector<uint32_t>> Tcomp32CopBa_s0OutPtr;
template<typename inBufferType=Tcomp32CopBa_s0OutPtr, typename outBufferType=Tcomp32CopBa_s0OutPtr>

class Tcomp32CopBaStep {

 protected:
  //output buffer related
  size_t outIdxBase;
  size_t outCnt;
  size_t outMax;
  //placed at the end of inner loop
  BarrierPtr tailBarrier;
  //input buffer related
  size_t inIdxBase;
  size_t inCnt;
  size_t inMax;
  //placed at the beginnig of inner loop
  BarrierPtr headBarrier;
  bool shouldStop = false;
  stopQueuePtr stopQueue;
  size_t batchCnt = 0;
  size_t batchMax = 0;
 public:
  inBufferType inputBuffer;
  outBufferType outputBuffer;
  Tcomp32CopBaStep() {}
  ~Tcomp32CopBaStep() {}
  //init the input functions
  virtual void initInput(size_t base, size_t len, BarrierPtr bar, inBufferType buf) {
    inIdxBase = base;
    inCnt = 0;
    inMax = base + len;
    headBarrier = bar;
    inputBuffer = buf;
    stopQueue = make_shared<INTELLI::SPSCQueue<char>>(1);
  }
  //init the output functions
  //init the input functions
  virtual void initOutput(size_t base, size_t len, BarrierPtr bar, outBufferType buf) {
    outIdxBase = base;
    outCnt = 0;
    outMax = base + len;
    tailBarrier = bar;
    outputBuffer = buf;
  }
  void setStop(size_t cnt) {
    batchMax = cnt;
    batchCnt = 0;
  }
  bool stopCondition() {
    batchCnt++;
    if (batchCnt >= batchMax) {
      return true;
    } else {
      return false;
    }
  }

};
class Tcomp32CopBaS0 : public AbstractThread, public Tcomp32CopBaStep<Tcomp32CopBa_s0OutPtr, Tcomp32CopBa_s0OutPtr> {
 public:
  Tcomp32CopBaS0() {}
  ~Tcomp32CopBaS0() {}
  void initInput(size_t base, size_t len, BarrierPtr bar, Tcomp32CopBa_s0OutPtr buf) {
    inIdxBase = base;
    inCnt = 0;
    inMax = base + len;
    headBarrier = bar;
    inputBuffer = buf;
    inputQueue = make_shared<INTELLI::SPSCQueue<uint32_t>>(len);
    isFirstRun = true;
  }
  void inputData(uint32_t da) {
    inputQueue->push(da);
  }
 protected:
  void threadMain();
  bool isFirstRun = true;
  Tcomp32CopBa_s0InQueuePtr inputQueue;

};
class Tcomp32CopBa_s1S2Info {
 public:
  Tcomp32CopBa_s1S2Info() {}
  ~Tcomp32CopBa_s1S2Info() {}
  uint64_t value;
  uint32_t len;
};
typedef std::shared_ptr<vector<Tcomp32CopBa_s1S2Info>> Tcomp32CopBa_s1OutPtr;
class Tcomp32CopBaS1 : public AbstractThread, public Tcomp32CopBaStep<Tcomp32CopBa_s0OutPtr, Tcomp32CopBa_s1OutPtr> {
 public:
  Tcomp32CopBaS1() {}
  ~Tcomp32CopBaS1() {}
 protected:
  void threadMain();
};
class Tcomp32CopBaS2 : public AbstractThread, public Tcomp32CopBaStep<Tcomp32CopBa_s1OutPtr, Tcomp32CopBa_s1OutPtr> {
 public:
  Tcomp32CopBaS2() {}
  ~Tcomp32CopBaS2() {}
  void setOutputLen(size_t len) {
    outBuf = std::shared_ptr<ADB::memCeil_t>(new ADB::memCeil_t[len],
                                             [](ADB::memCeil_t *p) {
                                               delete[] p;
                                             });
    outStream = make_shared<MemAddresser>(outBuf.get(), len);
  }
  size_t getOutLen() {
    //  return outStream->numberOfBitsUsed;
    return outBits;
  }
 protected:
  memPtr_shared outBuf;
  MemAddresserPtr outStream;
  size_t outBits;
  void threadMain();
};
typedef std::shared_ptr<Tcomp32CopBaS0> Tcomp32CopBaS0Ptr;
typedef std::shared_ptr<Tcomp32CopBaS1> Tcomp32CopBaS1Ptr;
typedef std::shared_ptr<Tcomp32CopBaS2> Tcomp32CopBaS2Ptr;
class Tcomp32CopBa {
 protected:
  size_t outBufLen = 10000;
  size_t cores;
  size_t batchCnt = 0;
  size_t splitCnt = 0;
  size_t splitIdx = 0;
 public:
  vector<Tcomp32CopBaS2Ptr> s2Threads;
  vector<size_t> s2Rate;

  vector<Tcomp32CopBaS1Ptr> s1Threads;
  vector<size_t> s1Rate;
  vector<Tcomp32CopBaS0Ptr> s0Threads;
  vector<size_t> s0Rate;
  vector<size_t> splitRate;
  BarrierPtr s01Bar, s12Bar, s20Bar;
  Tcomp32CopBa_s0OutPtr s01Buffer;
  Tcomp32CopBa_s1OutPtr s12Buffer;
  //all steps share the ratio
  void initThreads(size_t bigCoreWeight,
                   size_t littleCoreWeight,
                   size_t bigCores,
                   size_t littleCores,
                   size_t batchSize);
  void initThreads(float bigCoreRatio, size_t bigCores, size_t littleCores, size_t batchSize) {
    float littleW = (1 - bigCoreRatio) * batchSize;
    float bigW = bigCoreRatio * batchSize;
    size_t bw = (size_t) bigW;
    size_t lw = (size_t) littleW;
    initThreads(bw, lw, bigCores, littleCores, batchSize);
  }
  //with seperated ratio
  void initThreads(vector<size_t> bigCoreWeight,
                   vector<size_t> littleCoreWeight,
                   size_t bigCores,
                   size_t littleCores,
                   size_t batchSize);
  void initThreads(vector<float> bigCoreRatio, size_t bigCores, size_t littleCores, size_t batchSize) {
    size_t steps = bigCoreRatio.size();
    vector<size_t> bw(steps);
    vector<size_t> lw(steps);
    for (size_t i = 0; i < steps; i++) {
      float littleW = (1 - bigCoreRatio[i]) * batchSize;
      float bigW = bigCoreRatio[i] * batchSize;
      bw[i] = (size_t) bigW;
      lw[i] = (size_t) littleW;
    }
    initThreads(bw, lw, bigCores, littleCores, batchSize);
  }
  void run();
  void stop();
  void setOutLen(size_t _ol) {
    outBufLen = _ol;
  }
  void setBatches(size_t bs) {
    batchCnt = bs;
  }
  void inputData(uint32_t da);
  size_t getOutLen() {
    size_t ru = 0;
    for (size_t i = 0; i < cores; i++) {
      ru += s2Threads[i]->getOutLen();
    }
    return ru;
  }
};
}
#endif //ALIANCEDB_INCLUDE_COPROCESSING_TCOMP32COPBA_H_
