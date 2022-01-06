#ifndef ADB_INCLUDE_PARTITIONRUNNERS_ABSTRACTPARTITIONRUNNERS_HPP_
#define ADB_INCLUDE_PARTITIONRUNNERS_ABSTRACTPARTITIONRUNNERS_HPP_
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <Utils/MultiCore/SPSCQueue.hpp>
#include <Utils/MemAddresser.hpp>
#include <CommonData/CommonData.hpp>
#include <barrier>
#include <Utils/UtilityFunctions.hpp>
#include <numeric>
#include <MeterHelp.hpp>
using namespace std;
using namespace ADB;
using namespace DIVERSE_METER;
namespace ADB {
/*class:AbstractPPUnit
description: The base class of a parallel units in a partition runner

date:202001113
*/
class AbstractPPUnit : public AbstractThread {
 protected:

  memPtr pSrc;
  length_t numberOfBits;
  length_t mySafeSize, mySrcLen;
  string nameTag;
  virtual void puFunction() {}
  void threadMain() {
    // create inside the thread
  
    puFunction();
    //numberOfBits=outStream->numberOfBitsUsed;
  }
 public:
  memPtr_shared midResult, midInput;
  // MemAddresserPtr inStream, outStream;
  AbstractPPUnit(ADB::memPtr inP, length_t startByte, length_t len, length_t safeSize);
  ~AbstractPPUnit() {}
  length_t getUsedBits(void) {
    return numberOfBits;
  }
  length_t getSrcLen(void) {
    return mySrcLen;
  }
  string getName(void) {
    return nameTag;
  }

};
typedef std::shared_ptr<AbstractPPUnit> AbstractPPUnitPtr;
/*class:AbstractPartitionRunner
description: The base class of a whole partition job

date:202001015
*/
class AbstractPartitionRunner {
 protected:
  /* data */
  length_t inS, outS, safetySize;
  memPtr inP, outP;
  length_t partitions;
  vector<AbstractPPUnitPtr> pus;
  length_t numberOfBits;
  std::vector<int> partitionWeight;
  std::vector<int> partitionSizes;
  std::vector<int> partitionRemap;
  std::vector<int> partitionSizesFinal;
  std::vector<int> partitionRemapFinal;
  std::vector<int> partitionSafeSize;
  std::vector<int> partitionSafeSizeFinal;
  std::string subName;
  AbstractMeterPtr powerMeter = nullptr;
  int mainCpu = -1;
  ThreadPerf myPerf, myPerf2;
  std::string estabResult, collectionResult;
  double ipmEst = 1.0, ipmCollect = 1.0;
 public:
  AbstractPartitionRunner();
  AbstractPartitionRunner(ADB::length_t inS,
                          ADB::length_t outS,
                          ADB::length_t safetySize,
                          ADB::memPtr inP,
                          ADB::memPtr outP);
  ~AbstractPartitionRunner();
  //set up the power meter
  void setUpMeter() {
    powerMeter = newEnergyMeter();
  }
  //IPM of set up and collection
  virtual double getIpmOfEstablish() {
    return myPerf.getIpm(inS);
  }
  virtual double getIpmOfCollection() {
    return myPerf2.getIpm(inS);
  }
  uint64_t allRunTime, establishTime, collectTime;
  /*set the partion plan by vector
    format [ppunits], [cpuNo],*ppunits, [weight],*ppunits
    this function have self-check of size and weights
    for example, if you have 4 cores (0~3) and want an equal share, the vector should be:
    4 0 1 2 3 1 1 1 1
    */
  void setPartitionVector(std::vector<int> pv);
  void rebindByVector(std::vector<int> pv) {
    setPartitionVector(pv);
  }
  void setMainCpu(int cpu) {
    mainCpu = cpu;
  }
  //reset the partition numbers, called before the real execution
  void resetPartitions(length_t n);

  //template for weighted partition

  MemAddresserPtr outStream;
  virtual void establishPPUnits() {

  }
  virtual void collectResults() {

  }
  void unalignedCollection() {
    ipmCollect = 2.0;
    for (size_t i = 0; i < pus.size(); i++) {
      AbstractPPUnitPtr pp = pus[i];
      outStream->writeBits(pp->midResult.get(), pp->getUsedBits());
    }
  }
  void alignedCollection() {
    ipmCollect = 1.0;
    for (size_t i = 0; i < pus.size(); i++) {
      AbstractPPUnitPtr pp = pus[i];
      outStream->writeAlignedBytes(pp->midResult.get(), pp->getUsedBits() >> 3);
    }
  }
  //the function to start a partition-based running process
  void execute(void);
  //run each PU sequentially to profile without block
  void seqProfile();
  //print the stage name,id, cpu bind and latency
  void printStages();
  //out put to csv file
  void outputStages2Csv(std::string fname);
  // template of average partition, puType should be the derived class of AbstractPPUnit
  template<typename puType>
  void avgPartition(length_t alignedSize) {
    // length_t
    length_t divideLen = inS / alignedSize / partitions;
    divideLen *= alignedSize;
    length_t tSafeSize = safetySize / alignedSize / partitions;
    tSafeSize *= alignedSize;
    length_t tBegin;
    tBegin = 0;

    //set up ppus
    for (length_t i = 0; i < partitions - 1; i++) {
      std::shared_ptr<puType> pp = make_shared<puType>(inP, tBegin, divideLen, tSafeSize);
      // printf("assign %d bytes,from %d\r\n",divideLen,tBegin);
      pp->setBind(i);
      tBegin += divideLen;
      pus.push_back(pp);

    }
    //last run
    tSafeSize = safetySize - tSafeSize * (partitions - 1);
    length_t lastLen = inS - tBegin;
    std::shared_ptr<puType> pp = make_shared<puType>(inP, tBegin, lastLen, tSafeSize);
    pp->setBind(partitions - 1);
    //printf("assign %d bytes,from %d\r\n",lastLen,tBegin);
    pus.push_back(pp);
  }
//template for weighted partition
  template<typename puType>
  bool weightedPartition(length_t alignedSize) {
    if (partitionRemap.size() == 0) {
      ADB_WARNING("no valid partion plan, using defauly avg partiton\r\n");
      avgPartition<puType>(alignedSize);

      return false;
    }
    //try to build the sizes
    length_t fraction = accumulate(partitionWeight.begin(), partitionWeight.end(), 0);
    // printf("fraction=%d\r\n",fraction);
    length_t tsize, ssize;
    for (size_t i = 0; i < partitionWeight.size() - 1; i++) {
      tsize = inS / alignedSize * partitionWeight[i] / fraction;
      tsize *= alignedSize;
      ssize = safetySize * partitionWeight[i] / fraction;
      partitionSafeSize.push_back(ssize);
      partitionSizes.push_back(tsize);
    }
    tsize = inS - accumulate(partitionSizes.begin(), partitionSizes.end(), 0);
    partitionSizes.push_back(tsize);
    ssize = safetySize - accumulate(partitionSafeSize.begin(), partitionSafeSize.end(), 0);
    partitionSafeSize.push_back(ssize);
    //check if the partition is vaild
    for (size_t i = 0; i < partitionSizes.size(); i++) {

      if (partitionSizes[i] != 0) {
        partitionSizesFinal.push_back(partitionSizes[i]);
        partitionRemapFinal.push_back(partitionRemap[i]);
        partitionSafeSizeFinal.push_back(partitionSafeSize[i]);
      }
    }
    //printf("final partition sizes:\r\n");
    length_t tBegin = 0;
    resetPartitions(partitionSizesFinal.size());
    for (size_t i = 0; i < partitionSizesFinal.size(); i++) {
      //  printf("cpu%d,length=%d,safety %d bytes bytes\r\n",partitionRemapFinal[i],partitionSizesFinal[i],partitionSafeSizeFinal[i]);
      std::shared_ptr<puType> pp = make_shared<puType>(inP, tBegin, partitionSizesFinal[i], partitionSafeSizeFinal[i]);
      tBegin += partitionSizesFinal[i];
      pp->setBind(partitionRemapFinal[i]);
      pus.push_back(pp);
    }
    return true;
    /*resetPartitions(partitionVec[0]);
  // length_t
   length_t divideLen=inS/alignedSize/partitions;
   divideLen*=alignedSize;
   length_t tSafeSize=safetySize/alignedSize/partitions;
   tSafeSize*=alignedSize;
   length_t tBegin;
   tBegin=0;

   //set up ppus
   for (length_t i=0;i<partitions-1;i++)
   {
       std::shared_ptr<puType> pp=make_shared<puType>(inP,tBegin,divideLen,tSafeSize);
         printf("assign %d bytes,from %d\r\n",divideLen,tBegin);
       pp->setBind(i);
       tBegin+=divideLen;
        pus.push_back(pp);

   }
   //last run
   tSafeSize=safetySize-tSafeSize*(partitions-1);
   length_t lastLen=inS-tBegin;
    std::shared_ptr<puType> pp=make_shared<puType>(inP,tBegin,lastLen,tSafeSize);
    pp->setBind(partitions-1);
    printf("assign %d bytes,from %d\r\n",lastLen,tBegin);
    pus.push_back(pp);*/
  }
 private:
  void inlineEstablishPPU() {

    myPerf.start();
    establishPPUnits();
    myPerf.end();

    establishTime = myPerf.getRunTime();
    //estabResult=myPerf.resultStringCsv();
  }
  void inlineCollectResults() {
    myPerf2.start();
    collectResults();
    myPerf2.end();
    collectTime = myPerf2.getRunTime();
    // collectionResult=myPerf2.resultStringCsv();
  }
};

}

#endif