//
// Created by Tony Zeng on 14/08/2021.
//

#ifndef ADB_SRC_UTILS__TIME_TESTBENCH_HPP_
#define ADB_SRC_UTILS__TIME_TESTBENCH_HPP_

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
#include <CompressionQuery/CompressionQuery.hpp>
#include <CompressionComponents/AbstractComponent.hpp>

using namespace ADB;
namespace ADB {
/*class:TimeTestBench
description: The virtual test bench of running time, of a compression query, etc.
input:null
output:null
date:20200827
*/
class TimeTestBench {
 private:
  /* data */
  struct timeval tStart, tEnd;
  //struct libperf_data perfData;
 public:
  TimeTestBench();

  ~TimeTestBench();
  // uint64_t runTest(void *ptr);
  length_t runTest(CompressionQuery &cq, query_type_t type);
  void perfBegin(void);
  void perfEnd(void);
  //void runCompExeFunc(AbstractComponent &ac);
  void runCompExeFunc(AbstractComponentPtr ac);
  uint64_t lastTime;
};
}
#endif