#ifndef ADB_INCLUDE_UTILS_CPP11CLOCK_HPP_
#define ADB_INCLUDE_UTILS_CPP11CLOCK_HPP_
#include<chrono>
#include <stdio.h>
#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <string>
#include <condition_variable>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
using namespace std;
using namespace std::chrono;
namespace CPP11_CLOCK {
class Cpp11Clock {
 private:
  /* data */
  struct timeval tstart, tend;
  std::chrono::high_resolution_clock::time_point t0, t1;
  uint64_t tsc_old;
  uint64_t tsc_new;
 public:
  Cpp11Clock(/* args */) {
    reset();
    //  rdtsc_init();
  }
  ~Cpp11Clock() {

  }
  void reset() {
    t0 = high_resolution_clock::now();
    gettimeofday(&tstart, NULL);
    tend = tstart;
    /*tsc_old = rdtsc_new();
    tsc_new=tsc_old;*/
    // t1=t0;
  }
  int64_t getUs() {
    return duration_cast<chrono::microseconds>(high_resolution_clock::now() - t0).count();
  }
  int64_t getLinuxUs() {
    gettimeofday(&tend, NULL);
    int64_t s0, e0, s1, e1;
    s0 = tstart.tv_sec;
    s1 = tstart.tv_usec;
    e0 = tend.tv_sec;
    e1 = tend.tv_usec;
    return 1000000 * (e0 - s0) + (e1 - s1);
  }
  int64_t getNs() {
    return duration_cast<chrono::nanoseconds>(high_resolution_clock::now() - t0).count();
    //return duration_cast<chrono::nanoseconds>high_resolution_clock::now().count();
  }
  /* uint64_t getUsRdtsc()
    {
        tsc_new= rdtsc_new();
        return rdtsc_us(tsc_old,tsc_new);
    }*/
};
}

#endif