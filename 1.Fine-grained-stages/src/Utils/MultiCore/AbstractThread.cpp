#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/UtilityFunctions.hpp>
using namespace ADB;

#include <time.h>
#include <sched.h>
#include <pthread.h>
#include<cstdlib>
#include<time.h>
#include <Utils/Logger.hpp>
#define AT_ERROR ADB_ERROR

//stand-alone functions
length_t ADB::checkCpuBind(length_t bind) {
  length_t maxCpu = std::thread::hardware_concurrency();
  length_t ru;
  if (bind >= 0 && bind < maxCpu) {
    return bind;
  }
  srand(time(NULL));
  ru = rand() % maxCpu;

  return ru;
}
void ADB::bind2Cpu(int cpuId) {
  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(cpuId, &mask);
  if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0) {
        AT_ERROR("Error: setaffinity()\n");
    exit(0);
  }
  return;
}
//Abstract Thread
AbstractThread::AbstractThread(/* args */) {

  /*auto fun = [this]() {
    inlineRun();
  };
  threadPtr = std::make_shared<std::thread>(fun);*/
  uuId = (length_t) this;
  cpuBind = -1;
}
AbstractThread::AbstractThread(length_t _uuId, length_t _cpuBind) {

  uuId = _uuId;
  cpuBind = _cpuBind;

  //threadPtr->
}
AbstractThread::~AbstractThread() {

}

//the private inlineRun
void AbstractThread::inlineRun() {
  int i = checkCpuBind(cpuBind);
  bind2Cpu(i);
  myPerf = ThreadPerf(i);
  // printf("bind to core %d:%d\r\n", cpuBind, i);
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);
  myPerf.start();
  threadMain();
  gettimeofday(&tend, NULL);
  myPerf.end();
  runTime = UtilityFunctions::getRunningUs(tstart, tend);
}
// can be derived, real run loop
void AbstractThread::threadMain() {

}

void AbstractThread::join() {

  threadPtr->join();
}
void AbstractThread::start() {
  auto fun = [this]() {
    inlineRun();
  };
  threadPtr = std::make_shared<std::thread>(fun);
}

void AbstractThread::detach() {
  threadPtr->detach();
}
void AbstractThread::setBarrier(BarrierPtr bptr) {
  myBarrier = bptr;
}
void AbstractThread::setBind(length_t cpuI) {
  cpuBind = cpuI;
}