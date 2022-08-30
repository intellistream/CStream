/**
 * @brief This is the main entry point of the entire program.
 * Users will typically access this file to use the stream clustering algorithm.
 * We use this as the entry point for benchmarking.
 */
/**
 * @brief This is the main entry point of the entire program.
 * Users will typically access this file to use the stream clustering algorithm.
 * We use this as the entry point for benchmarking.
 */

#include <Utils/Logger.hpp>
#include <Utils/TimeTestBench.hpp>
#include <Utils/UtilityFunctions.hpp>
#include <Utils/FileSp.hpp>
#include <CompLibs/CompLibLz4.hpp>
#include <CompLibs/CompLibZlib.hpp>
#include <CompLibs/CompLibTcomp32.hpp>
#include <CompLibs/CompLibFse.hpp>
#include <CompLibs/CompLibTrle.hpp>
#include <filesystem>
#include <CompressionComponents/AbstractComponent.hpp>
#include <Utils/MemAddresser.hpp>
#include <CompressionTasks/Tcomp32Task.hpp>
#include <CompressionTasks/LZ4Task.hpp>
#include <CompressionTasks/Tdic32Task.hpp>
#include <PipeLines/AbstractPipeLine.hpp>
#include <PipeLines/Tcomp32PipeLine2S.hpp>
#include <PipeLines/Tdic32PipeLine2S.hpp>
#include <PipeLines/Tdic32PipeLine3S.hpp>
#include <PipeLines/FakePipeLine.hpp>
#include <PipeLines/LZ4PipeLine.hpp>
#include <PartitionRunners/Tcomp32PartitionRunner.hpp>
#include <PartitionRunners/Tdic32PartitionRunner.hpp>
#include <PartitionRunners/LZ4PartitionRunner.hpp>
#include <Utils/PerfTool.hpp>
#include <Utils/Math/LeastSquare.hpp>

#include <Utils/Math/SegLinearFit.hpp>
using namespace std;
using namespace ADB;
using namespace FILE_SP;
using namespace INTELLI;
using namespace MATH_FUNC;
int g_mainCpu;
int fakeRatio;
// this template function can be used for both pipeline and partition, by just assign a puType
template<typename puType>
void testParaPlan(string tag,
                  ADB::length_t inS,
                  ADB::length_t outS,
                  ADB::length_t safetySize,
                  ADB::memPtr inP,
                  ADB::memPtr outP,
                  std::vector<int> rmv) {
  std::shared_ptr<puType> pe = make_shared<puType>(inS, outS, safetySize, inP, outP);
  pe->rebindByVector(rmv);
  printf("%s run parallel execution\r\n", tag.data());
  pe->setMainCpu(g_mainCpu);
  pe->execute();
  printf("%dus:%ld-%ld\r\n", pe->allRunTime, inS, pe->outStream->numberOfBitsUsed / 8);
  std::shared_ptr<puType> se = make_shared<puType>(inS, outS, safetySize, inP, outP);
  se->rebindByVector(rmv);
  se->setMainCpu(g_mainCpu);
  printf("%s run seq execution\r\n", tag.data());
  se->seqProfile();
  printf("%dus:%ld-%ld\r\n", se->allRunTime, inS, se->outStream->numberOfBitsUsed / 8);
  pe->outputStages2Csv(tag + "_pe.csv");
  se->outputStages2Csv(tag + "_se.csv");
}
template<typename puType>
void testParaPlanWithSleep(string tag,
                  ADB::length_t inS,
                  ADB::length_t outS,
                  ADB::length_t safetySize,
                  ADB::memPtr inP,
                  ADB::memPtr outP,
                  std::vector<int> rmv) {
  std::shared_ptr<puType> pe = make_shared<puType>(inS, outS, safetySize, inP, outP);
  pe->rebindByVector(rmv);
  printf("%s,%d delay run parallel execution\r\n", tag.data(),fakeRatio);
  pe->setMainCpu(g_mainCpu);
  pe->setPar(fakeRatio);
  pe->execute();
  printf("%dus:%ld-%ld\r\n", pe->allRunTime, inS, pe->outStream->numberOfBitsUsed / 8);
  pe->outputStages2Csv(tag + "_pe.csv");
 /* std::shared_ptr<puType> se = make_shared<puType>(inS, outS, safetySize, inP, outP);
  se->rebindByVector(rmv);
  se->setMainCpu(g_mainCpu);
  printf("%s run seq execution\r\n", tag.data());
  se->setPar(fakeRatio);
  se->seqProfile();
  printf("%dus:%ld-%ld\r\n", se->allRunTime, inS, se->outStream->numberOfBitsUsed / 8);
  pe->outputStages2Csv(tag + "_pe.csv");
  se->outputStages2Csv(tag + "_se.csv");*/
}
template<typename puType> vector<double> autoProfilePipe(string tag,
                  ADB::length_t inS,
                  ADB::length_t outS,
                  ADB::length_t safetySize,
                  ADB::memPtr inP,
                  ADB::memPtr outP,
                  std::vector<int> rmv
                  ) {
                    vector<double> ru(2);

 std::shared_ptr<puType> se = make_shared<puType>(inS, outS, safetySize, inP, outP);
  se->rebindByVector(rmv);
  se->setMainCpu(g_mainCpu);
  se->seqProfile();
  printf("%dus:%ld-%ld\r\n", se->allRunTime, inS, se->outStream->numberOfBitsUsed / 8);
  se->outputStages2Csv(tag + '_' + to_string(fakeRatio)+"_se.csv");
  ru[0]=se->getStage(0)->getRunTime();
  ru[1]=se->getStage(1)->getRunTime();
  return ru;
}
void autoProfileLz4LL( ADB::length_t inS,
                  ADB::length_t outS,
                  ADB::length_t safetySize,
                  ADB::memPtr inP,
                  ADB::memPtr outP)
{
vector<double> latencyS0;
vector<double> latencyS1;
vector<double> size;
vector<double> tempRu;
//std::vector<int> rmvBB={4,5};
std::vector<int> rmvLL={1,2};
//1
fakeRatio=1;
tempRu=autoProfilePipe<LZ4PipeLine>("lz4_pipe2_LL",inS/fakeRatio,outS/fakeRatio,safetySize/fakeRatio,inP,outP,rmvLL);
size.push_back(inS/fakeRatio);
latencyS0.push_back(tempRu[0]);
latencyS1.push_back(tempRu[1]);


fakeRatio=2;
tempRu=autoProfilePipe<LZ4PipeLine>("lz4_pipe2_LL",inS/fakeRatio,outS/fakeRatio,safetySize/fakeRatio,inP,outP,rmvLL);
size.push_back(inS/fakeRatio);
latencyS0.push_back(tempRu[0]);
latencyS1.push_back(tempRu[1]);

fakeRatio=5;
tempRu=autoProfilePipe<LZ4PipeLine>("lz4_pipe2_LL",inS/fakeRatio,outS/fakeRatio,safetySize/fakeRatio,inP,outP,rmvLL);
size.push_back(inS/fakeRatio);
latencyS0.push_back(tempRu[0]);
latencyS1.push_back(tempRu[1]);


fakeRatio=10;
tempRu=autoProfilePipe<LZ4PipeLine>("lz4_pipe2_LL",inS/fakeRatio,outS/fakeRatio,safetySize/fakeRatio,inP,outP,rmvLL);
size.push_back(inS/fakeRatio);
latencyS0.push_back(tempRu[0]);
latencyS1.push_back(tempRu[1]);


fakeRatio=20;
tempRu=autoProfilePipe<LZ4PipeLine>("lz4_pipe2_LL",inS/fakeRatio,outS/fakeRatio,safetySize/fakeRatio,inP,outP,rmvLL);
size.push_back(inS/fakeRatio);
latencyS0.push_back(tempRu[0]);
latencyS1.push_back(tempRu[1]);

LeastSquare lsm_s0(size,latencyS0);
LeastSquare lsm_s1(size,latencyS1);
printf("LL:\r\nstage0:%s,cor=%lf\r\nstage1:%s,cor=%lf\r\n",lsm_s0.getEquation().data(),lsm_s0.getCorelation(),lsm_s1.getEquation().data(),lsm_s1.getCorelation());
}
/*
void testFakeOnly(string tag,
                  ADB::length_t inS,
                  ADB::length_t outS,
                  ADB::length_t safetySize,
                  ADB::memPtr inP,
                  ADB::memPtr outP,
                  std::vector<int> rmv) {
  FakePipeLinePtr pe = make_shared<FakePipeLine>(inS, outS, safetySize, inP, outP);
  pe->rebindByVector(rmv);
  pe->setIdleCnt(10, 10 * fakeRatio);
  printf("fake run parallel execution,ratio%d\r\n", fakeRatio);
  pe->setMainCpu(g_mainCpu);
  pe->execute();
  printf("%dus:%ld-%ld\r\n", pe->allRunTime, inS, pe->outStream->numberOfBitsUsed / 8);
  FakePipeLinePtr se = make_shared<FakePipeLine>(inS, outS, safetySize, inP, outP);
  se->rebindByVector(rmv);
  se->setIdleCnt(10, 10 * fakeRatio);
  printf("fake run seq execution\r\n");
  se->setMainCpu(g_mainCpu);
  se->seqProfile();
  printf("%dus:%ld-%ld\r\n", se->allRunTime, inS, se->outStream->numberOfBitsUsed / 8);
  pe->outputStages2Csv(tag + '_' + to_string(fakeRatio) + "_pe.csv");
  se->outputStages2Csv(tag + '_' + to_string(fakeRatio) + "_se.csv");
}*/
/*
void testPartitionOnly (string tag,
                  ADB::length_t inS2,
                  ADB::length_t outS2,
                  ADB::length_t safetySize2,
                  ADB::memPtr inP,
                  ADB::memPtr outP,
                  std::vector<int> rmv) {
ADB::length_t szt=inS2/fakeRatio;
ADB::length_t safetySize=safetySize2/fakeRatio;
ADB::length_t outS=outS2/fakeRatio;
testParaPlan<LZ4PartitionRunner>("lz4_" + tag+"_"+to_string(fakeRatio), szt, outS,safetySize , inP, outP, rmv);
 testParaPlan<Tcomp32PartitionRunner>("tcomp32_" + tag+"_"+to_string(fakeRatio), szt, outS, safetySize, inP, outP, rmv);
  testParaPlan<Tdic32PartitionRunner>("tdic32_" + tag+"_"+to_string(fakeRatio), szt, outS, safetySize, inP, outP, rmv);
}*/

void testPipeLineOnly (string tag,
                  ADB::length_t inS2,
                  ADB::length_t outS2,
                  ADB::length_t safetySize2,
                  ADB::memPtr inP,
                  ADB::memPtr outP,
                  std::vector<int> rmv) {
ADB::length_t szt=inS2/fakeRatio;
ADB::length_t safetySize=safetySize2/fakeRatio;
ADB::length_t outS=outS2/fakeRatio;
testParaPlan<LZ4PipeLine>("lz4_pipe2_" + tag+"_"+to_string(fakeRatio), szt, outS,safetySize , inP, outP, rmv);
testParaPlan<Tcomp32PipeLine2S>("tcomp32_pipe2_" + tag+"_"+to_string(fakeRatio), szt, outS, safetySize, inP, outP, rmv);
testParaPlan<Tdic32PipeLine2S>("tdic32_pipe2_" + tag+"_"+to_string(fakeRatio), szt, outS, safetySize, inP, outP, rmv);

//testParaPlan<FakePipeLine>("fake_" + tag+"_"+to_string(fakeRatio), szt, outS, safetySize, inP, outP, rmv);
}
void testFetchOnly(string tag,
                  ADB::length_t inS,
                  ADB::length_t outS,
                  ADB::length_t safetySize,
                  ADB::memPtr inP,
                  ADB::memPtr outP,
                  std::vector<int> trmv) {


vector <int> rmv0;
rmv0={3};
testParaPlanWithSleep<Tdic32PipeLineOnlyFeed>("tdic32_feed_" + tag+"_"+to_string(1), inS/1, outS,safetySize , inP, outP, rmv0);
rmv0.push_back(trmv[0]);
rmv0.push_back(trmv[1]);
testParaPlanWithSleep<Tcomp32PipeLine>("tdic32_pipe3_" + tag+"_"+to_string(1), inS/1, outS,safetySize , inP, outP, rmv0);

//testParaPlan<FakePipeLine>("fake_" + tag+"_"+to_string(fakeRatio), szt, outS, safetySize, inP, outP, rmv);
}
typedef std::shared_ptr<int> intPtr;
/*int main ()
{
  ThreadPerf pp;
  pp.setUpTransitVec();
  vector <double> k=pp.getTransitVec();
  for (int i=0;i<k.size();i++)
  {
    printf("%lf,\r\n",k[i]);
  }
  return 0;
}*/
/*int main()
{
  vector<double> x={1,5,3,4,2};
  vector<double> y={2,9,5,7,3};
  //vector<double> seg={0,2.5,6553};
  SegLinearFit sf(x,y,0.1);
  printf("%s\r\n",sf.getEquation().data());
  printf("1.5:%lf,10.0:%lf\r\n",sf.forward(1.5),sf.forward(10.0));
  vector<double> y2=sf.forward(y);
  for(size_t i=0;i<y2.size();i++)
  {
    printf("%lf,",y2[i]);
  }
  return 0;
}*/
int main(int argc, char **argv) {

//just test pipeline
  setupLogging("benchmark.log", LOG_DEBUG);
  std::vector<int> p3Vec;
  std::vector<int> p2Vec;
  std::vector<int> parVec;
  std::string p3Str = "default";
  std::string parStr = "default";
  std::string p2Str = "default";
  if (argc < 2) {
    ADB_FATAL_ERROR("ERROR !!! NO INPUT  !! \n");
    return 0;
  }
  if (argc >= 3) {
    int id = atoi(argv[2]);
    id = checkCpuBind(id);
    bind2Cpu(id);
    printf("bind to cpu %d\r\n", id);
    g_mainCpu = id;
  }

  if (argc >= 4) {
    p3Str = "";
    p3Str += argv[3];
    p3Vec = UtilityFunctions::getIntVectorFromFile(argv[3]);
    size_t i;
    printf("3 stage pipeline plans:");
    for (i = 0; i < p3Vec.size(); i++) {
      printf("%d,", p3Vec[i]);
    }
    printf("\r\n");
  }

  if (argc >= 5) {
    p2Str = "";
    p2Str += argv[4];
    p2Vec = UtilityFunctions::getIntVectorFromFile(argv[4]);
    int i;
    printf("2 stage pipeline plans:");
    for (i = 0; i < p2Vec.size(); i++) {
      printf("%d,", p2Vec[i]);
    }
    printf("\r\n");
  }
  if (argc >= 6) {
    parStr = "";
    parStr += argv[5];
    parVec = UtilityFunctions::getIntVectorFromFile(argv[5]);
    size_t i;
    printf("partition plans:");
    for (i = 0; i < parVec.size(); i++) {
      printf("%d,", parVec[i]);
    }
    printf("\r\n");
  }
  if (argc >= 7) {
    fakeRatio = atoi(argv[6]);
  }
  std::string ltxt = "loading ";
  ltxt += argv[1];
  ADB_INFO(ltxt);
  ADB::length_t szt;
  memPtr_shared sourceBuf = loadByteFile(FILE_SP::autoUrl(argv[1]), &szt);
  if (!sourceBuf) {
    ADB_ERROR("Can not open file!");
    return 0;
  }
  ADB_INFO("open file: " + FILE_SP::autoUrl(argv[1]));

  memPtr_shared outBuf0 = std::shared_ptr<ADB::memCeil_t>(new ADB::memCeil_t[szt * 2],
                                                          [](ADB::memCeil_t *p) {
                                                            delete[] p;
                                                          });

//printf("\r\n/******single thread***/\r\n");
  /*struct timeval tstart, tend;
  Tcomp32Task t32Task = Tcomp32Task(szt, szt, szt, sourceBuf.get(), outBuf0.get());
  gettimeofday(&tstart, NULL);
  t32Task.runForwardTask();
  gettimeofday(&tend, NULL);
  uint32_t tu = UtilityFunctions::getRunningUs(tstart, tend);
  printf("tcomp32 one core,%dus:%ld-%ld\r\n", tu, szt, t32Task.outStream->numberOfBitsUsed / 8);
  LZ4Task lz4Task = LZ4Task(szt, szt, szt, sourceBuf.get(), outBuf0.get());
  gettimeofday(&tstart, NULL);
  lz4Task.runForwardTask();
  gettimeofday(&tend, NULL);
  tu = UtilityFunctions::getRunningUs(tstart, tend);
  printf("lz4 one core,%dus:%ld-%ld\r\n", tu, szt, lz4Task.outStream->numberOfBitsUsed / 8);
  Tdic32Task d32Task = Tdic32Task(szt, szt, szt, sourceBuf.get(), outBuf0.get());
  gettimeofday(&tstart, NULL);
  d32Task.runForwardTask();
  gettimeofday(&tend, NULL);
  tu = UtilityFunctions::getRunningUs(tstart, tend);
  printf("tdic32 one core,%dus:%ld-%ld\r\n", tu, szt, d32Task.outStream->numberOfBitsUsed / 8);*/
  /*testParaPlan<Tcomp32PipeLine>("tcomp32_pipe3_" + p3Str, szt, szt, szt, sourceBuf.get(), outBuf0.get(), p3Vec);
  testParaPlan<Tcomp32PipeLine2S>("tcomp32_pipe2_" + p2Str, szt, szt, szt, sourceBuf.get(), outBuf0.get(), p2Vec);
  //testParaPlan<FakePipeLine>("fake_"+p2Str,szt, szt, szt, sourceBuf.get(), outBuf0.get(),p2Vec);
  testParaPlan<LZ4PipeLine>("lz4_pipe2_" + p2Str, szt, szt, szt, sourceBuf.get(), outBuf0.get(), p2Vec);
  testParaPlan<LZ4PartitionRunner>("lz4_partition_" + parStr, szt, szt, szt, sourceBuf.get(), outBuf0.get(), parVec);*/
  /*testParaPlan<Tcomp32PartitionRunner>("tcomp32_partition_" + parStr,
                                       szt,
                                       szt,
                                       szt,
                                       sourceBuf.get(),
                                       outBuf0.get(),
                                       parVec);*/
  //testFakeOnly("fake_"+p2Str,szt, szt, szt, sourceBuf.get(), outBuf0.get(),p2Vec);
 /* testParaPlan<LZ4PartitionRunner>("lz4_partition_" + parStr, szt, szt, szt, sourceBuf.get(), outBuf0.get(), parVec);
  testParaPlan<Tcomp32PartitionRunner>("tcomp32_partition_" + parStr,
                                       szt,
                                       szt,
                                       szt,
                                       sourceBuf.get(),
                                       outBuf0.get(),
                                       parVec);*/
  //testPartitionOnly(parStr,szt, szt*2, szt*2, sourceBuf.get(), outBuf0.get(),parVec);
 testPipeLineOnly(p2Str,szt, szt*2, szt*2, sourceBuf.get(), outBuf0.get(),p2Vec);
//testFetchOnly(p2Str,szt, szt*2, szt*2, sourceBuf.get(), outBuf0.get(),p2Vec);
//autoProfileLz4LL(szt, szt*2, szt*2, sourceBuf.get(), outBuf0.get());
  return 0;
}
/*
int omain(int argc, char **argv) {
setupLogging("benchmark.log", LOG_DEBUG);
if (argc < 2) {
ADB_FATAL_ERROR("ERROR !!! NO INPUT  !! \n");
return 0;
}
if (argc >= 3) {
int id = atoi(argv[2]);
id = checkCpuBind(id);
bind2Cpu(id);
printf("bind to cpu %d\r\n", id);
}
std::string ltxt = "loading ";
ltxt += argv[1];
ADB_INFO(ltxt);
ADB::length_t szt;
memPtr_shared sourceBuf = loadByteFile(FILE_SP::autoUrl(argv[1]), &szt);
if (!sourceBuf) {
ADB_ERROR("Can not open file!");
return 0;
}
ADB_INFO("open file: " + FILE_SP::autoUrl(argv[1]));
memPtr_shared outBuf0 = std::shared_ptr<ADB::memCeil_t>(new ADB::memCeil_t[szt * 2],
[](ADB::memCeil_t *p) {
delete[] p;
});
memPtr_shared outBuf1 = std::shared_ptr<ADB::memCeil_t>(new ADB::memCeil_t[szt * 2],
[](ADB::memCeil_t *p) {
delete[] p;
});
TimeTestBench ttb;
CompLibTcomp32 tLib = CompLibTcomp32(szt, szt, szt, sourceBuf.get(), outBuf1.get());
uint32_t compedSize = ttb.runTest(tLib, ADB::COMP);
printf("%ldus-%ld\r\n", ttb.lastTime, compedSize);
//lz4
//zlib
CompibZlib zLib = CompLibZlib(szt, szt, szt, sourceBuf.get(), outBuf1.get());
compedSize = ttb.runTest(zLib, ADB::COMP);
printf("zLib %ld:%ld,%ld us\r\n", szt, compedSize, ttb.lastTime);
//tcomp32
CompLibTcomp32 tLib = CompLibTcomp32(szt, szt, szt, sourceBuf.get(), outBuf1.get());
compedSize = ttb.runTest(tLib, ADB::COMP);
if (!compedSize) {
  printf("error in tcomp, code %d\r\n", tLib.getError());
} else {
  printf("tcomp %ld:%ld,%ld us\r\n", szt, compedSize, ttb.lastTime);
}
//fse
CompLibFse fseLib = CompLibFse(szt, szt, szt, sourceBuf.get(), outBuf1.get());
compedSize = ttb.runTest(fseLib, ADB::COMP);
printf("fse %ld:%ld,%ld us\r\n", szt, compedSize, ttb.lastTime);
//turbo rle
CompLibTrle trleLib = CompLibTrle(szt, szt, szt, sourceBuf.get(), outBuf1.get());
compedSize = ttb.runTest(trleLib, ADB::COMP);
printf("turoboRLE %ld:%ld,%ld us\r\n", szt, compedSize, ttb.lastTime);
uint8_t tbuf[64];
for (int i = 0; i < 64; i++) {
  tbuf[i] = 0;
}
CompLibLz4 lz4Lib = CompLibLz4(szt, szt, szt, sourceBuf.get(), outBuf0.get());
compedSize = ttb.runTest(lz4Lib, ADB::COMP);
printf("LZ4 %ld:%ld,%ld us\r\n", szt, compedSize, ttb.lastTime);
//uint8_t arry[]={0xfa,0xfc,0xfd,0xfe};
//uint8_t *tstr= (uint8_t *)arry;
 length_t decomSize;
 decomSize = 0;
 Tcomp32Task t32Task = Tcomp32Task(szt, szt, szt, sourceBuf.get(), outBuf1.get());
 t32Task.profileForwardTask();
 t32Task.printProfile();
 printf("\r\n%ld", BITS_TO_BYTES(t32Task.outStream->numberOfBitsUsed));
 decomSize = BITS_TO_BYTES(t32Task.outStream->numberOfBitsUsed);
 memPtr_shared outBuf2 = std::shared_ptr<ADB::memCeil_t>(new ADB::memCeil_t[szt * 2],
                                                         [](ADB::memCeil_t *p) {
                                                           delete[] p;
                                                         });
 Tcomp32Task t32TaskBack = Tcomp32Task(decomSize, decomSize, decomSize, outBuf1.get(), outBuf2.get());
 t32TaskBack.profileBackwardTask();
 t32TaskBack.printBackwardProfile();
 printf("\r\n%ld", BITS_TO_BYTES(t32TaskBack.outStream->numberOfBitsUsed));
 decomSize = BITS_TO_BYTES(lz4Task.outStream->numberOfBitsUsed);
 printf("\r\n%ld", decomSize);
 lz4Task.reset(decomSize, szt, szt, outBuf0.get(), outBuf1.get());
 lz4Task.profileBackwardTask();
 lz4Task.printBackwardProfile();
 decomSize = (lz4Task.outStream->numberOfBitsUsed) >> 3;
 printf("\r\n%ld", decomSize);
//task0 tt0(100);
return 0;
}*/