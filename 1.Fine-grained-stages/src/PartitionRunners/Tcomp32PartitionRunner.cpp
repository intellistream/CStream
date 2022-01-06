#include <PartitionRunners/Tcomp32PartitionRunner.hpp>
#include <CompressionTasks/Tcomp32Task.hpp>
using namespace ADB;

Tcomp32PPUnit::Tcomp32PPUnit(ADB::memPtr inP, length_t startByte, length_t len, length_t safeSize) :
    AbstractPPUnit(inP, startByte, len, safeSize) {

}
void Tcomp32PPUnit::puFunction() {
  Tcomp32TaskPtr t32Task = make_shared<Tcomp32Task>(mySrcLen, mySafeSize, mySafeSize, pSrc, midResult.get());
  t32Task->runForwardTask();
  numberOfBits = t32Task->outStream->numberOfBitsUsed;
  nameTag = "tcomp32PU";
}
//the runner
Tcomp32PartitionRunner::Tcomp32PartitionRunner(/* args */) : AbstractPartitionRunner() {

}
Tcomp32PartitionRunner::Tcomp32PartitionRunner(ADB::length_t inS,
                                               ADB::length_t outS,
                                               ADB::length_t safetySize,
                                               ADB::memPtr inP,
                                               ADB::memPtr outP)
    : AbstractPartitionRunner(inS, outS, safetySize, inP, outP) {
  outStream = make_shared<MemAddresser>(outP, outS);
}
Tcomp32PartitionRunner::~Tcomp32PartitionRunner() {
}
void Tcomp32PartitionRunner::establishPPUnits() {   // length_t
  /* length_t divideLen=inS/4/partitions;
   divideLen*=4;
   length_t tSafeSize=safetSize/4/partitions;
   tSafeSize*=4;
   length_t tBegin;
   tBegin=0;

   //set up ppus
   for (length_t i=0;i<partitions-1;i++)
   {
       Tcomp32PPUnitPtr pp=make_shared<Tcomp32PPUnit>(inP,tBegin,divideLen,tSafeSize);
         printf("assign %d bytes,from %d\r\n",divideLen,tBegin);
       pp->setBind(i);
       tBegin+=divideLen;
        pus.push_back(pp);

   }
   //last run
   tSafeSize=safetSize-tSafeSize*(partitions-1);
   length_t lastLen=inS-tBegin;
    Tcomp32PPUnitPtr pp=make_shared<Tcomp32PPUnit>(inP,tBegin,lastLen,tSafeSize);
    pp->setBind(partitions-1);
    printf("assign %d bytes,from %d\r\n",lastLen,tBegin);
    pus.push_back(pp);*/
  //  printf("avg partition\r\n");
  weightedPartition<Tcomp32PPUnit>(4);
}
void Tcomp32PartitionRunner::collectResults() {
  //printf("unaligned collection\r\n");
  unalignedCollection();
}