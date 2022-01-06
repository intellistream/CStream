//
// Created by tony on 2021/10/13.
//

#ifndef ADB_INCLUDE_UTILS_MULTICORE_ABSTRACTTHREAD_H_
#define ADB_INCLUDE_UTILS_MULTICORE_ABSTRACTTHREAD_H_
#include <thread>
#include <CommonData/CommonData.hpp>
#include <barrier>
#include <Utils/PerfTool.hpp>
using namespace std;

namespace ADB {
void bind2Cpu(int cpuId);
length_t checkCpuBind(length_t bind);
typedef std::shared_ptr<std::barrier<>> BarrierPtr;

/*class:AbstractThread
description: The base class of c++11 thread

date:202001013
*/
class AbstractThread {

 private:
  std::shared_ptr<std::thread> threadPtr;
  BarrierPtr myBarrier;
  ThreadPerf myPerf;
  //this is the inline function
  void inlineRun(void);
  
 protected:
  //this function can be derived by son classes
  virtual void threadMain(void);
  //Ipm functions
  

  length_t runTime;
  string nameTag;
  length_t uuId, cpuBind;
 public:

  AbstractThread(/* args */);
  AbstractThread(length_t uuId, length_t cpuBind);

  ~AbstractThread();
  void join();
  void start();
  void detach();
  void setBarrier(BarrierPtr bptr);
  void setBind(length_t cpuBind);
  length_t getRunTime() {
    return runTime;
  }
  void setName(string name) {
    nameTag = name;
  }
  length_t getId() {
    return uuId;
  }
  length_t getCpu() {
    return cpuBind;
  }
  void setCpu(length_t _cpuBind) {
    cpuBind = _cpuBind;
  }
  string getName() {
    return nameTag;
  }

  string headStringPrintf(void) {
    return myPerf.headStringPrintf();
  }
  //for csv
  string headStringCsv(void) {
    return myPerf.headStringCsv();
  }
  //for printf
  string resultStringPrintf(void) {
    return myPerf.resultStringPrintf();
  }
  //for csv
  string resultStringCsv(void) {
    return myPerf.resultStringCsv();
  }
  // the IPM
  virtual double getIpm() {
    return 0;
  }
  double getinLineIpm(length_t mtimes) {
    return myPerf.getIpm(mtimes);
  }
  vector<double> getMemTransitVec(void) {
    myPerf.setUpTransitVec();
    return myPerf.getTransitVec();
  }
  void setMemTransitVec(vector<double> a) {
    myPerf.loadTransitVec(a);
  }

  // to check wether the bind is legal, or assign a random cpu

};

};
#endif 