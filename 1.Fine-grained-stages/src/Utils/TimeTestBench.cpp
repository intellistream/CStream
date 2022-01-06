// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

#include <Utils/TimeTestBench.hpp>
#include <Utils/UtilityFunctions.hpp>

TimeTestBench::TimeTestBench(/* args */) {
//libperf_initialize(&perfData,-1,-1);
//printf("init perf\r\n");
}

TimeTestBench::~TimeTestBench() {
  //libperf_close(&perfData);
}

/*function:runTest
description: run the test of specific CompressionQuery [&cq], assigned by [type]
input:CompressionQuery &cq, query_type_t type
output:null
date:20210827
*/
ADB::length_t TimeTestBench::runTest(CompressionQuery &cq, query_type_t type) {
  ADB::length_t ru = 0;
  gettimeofday(&tStart, NULL);
  switch (type) {
    case ADB::COMP:ru = cq.runCompression();
      break;
    case ADB::DECOM:ru = cq.runDecompression();
      break;
    default:break;
  }
  gettimeofday(&tEnd, NULL);
  lastTime = UtilityFunctions::getRunningUs(tStart, tEnd);
  return ru;
}

/*function:runCompExeFunc
description: run the test of backward funtion in [ac]
input:AbstractComponent &ac
output:null
date:20211004
*/
void TimeTestBench::runCompExeFunc(AbstractComponentPtr ac) {
  gettimeofday(&tStart, NULL);
  ac->exeFunction();
  gettimeofday(&tEnd, NULL);
  lastTime = UtilityFunctions::getRunningUs(tStart, tEnd);
  ac->profileInfo.runTime += lastTime;
  ac->writeArgFunction();
}

/*function:perfBegin
description: begin a single time of read perf
input:null
output:null
date:20211012
*/
void TimeTestBench::perfBegin() {

}

/*function:perfEnd
description: end a single time of read perf
input:null
output:null
date:20211012
*/
void TimeTestBench::perfEnd() {

}