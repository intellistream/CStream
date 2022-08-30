#include <PartitionRunners/LZ4PartitionRunner.hpp>
#include <CompressionTasks/LZ4Task.hpp>
//#include <lz4/lz4.h>
using namespace ADB;

LZ4PPUnit::LZ4PPUnit(ADB::memPtr inP, length_t startByte, length_t len, length_t safeSize) :
    AbstractPPUnit(inP, startByte, len, safeSize) {

}
void LZ4PPUnit::puFunction() {
  LZ4TaskPtr lz4Task = make_shared<LZ4Task>(mySrcLen, mySafeSize, mySafeSize, pSrc, midResult.get());
  lz4Task->runForwardTask();

  nameTag = "LZ4PU";
  numberOfBits = lz4Task->outStream->numberOfBitsUsed;
  // printf("forward done,%ld\r\n",lz4Task->outStream->numberOfBitsUsed>>3);
  //  numberOfBits=lz4Task.outStream->numberOfBitsUsed;
  /*  ADB::length_t ru;
 ru = LZ4_compress_fast((char *) pSrc, (char *) midResult.get(),mySrcLen , mySafeSize, 1);
    numberOfBits=ru<<3;*/
}
//the runner
LZ4PartitionRunner::LZ4PartitionRunner(/* args */) : AbstractPartitionRunner() {

}
LZ4PartitionRunner::LZ4PartitionRunner(ADB::length_t inS,
                                       ADB::length_t outS,
                                       ADB::length_t safetySize,
                                       ADB::memPtr inP,
                                       ADB::memPtr outP)
    : AbstractPartitionRunner(inS, outS, safetySize, inP, outP) {
  outStream = make_shared<MemAddresser>(outP, outS);
}
LZ4PartitionRunner::~LZ4PartitionRunner() {
}
void LZ4PartitionRunner::establishPPUnits() {

  weightedPartition<LZ4PPUnit>(4);
}
void LZ4PartitionRunner::collectResults() {
  //printf("unaligned collection\r\n");
  alignedCollection();
}