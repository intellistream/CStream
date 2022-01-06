#include <CompressionTasks/AbstractTask.hpp>
using namespace ADB;
using namespace std;
AbstractTask::AbstractTask(/* args */) {
}

AbstractTask::~AbstractTask() {
}
AbstractTask::AbstractTask(ADB::length_t inS,
                           ADB::length_t outS,
                           ADB::length_t _safetySize,
                           ADB::memPtr inP,
                           ADB::memPtr outP) {
  inStream = make_shared<MemAddresser>(inP, inS);
  outStream = make_shared<MemAddresser>(outP, outS);
  safetySize = _safetySize;
  stopPOS = inS;
  otherPtr = nullptr;
  compPtrFor = make_shared<std::vector<AbstractComponentPtr>>();
  compPtrBack = make_shared<std::vector<AbstractComponentPtr>>();
  mySrc = inP;
  myDest = outP;
  /*myComponent=*compPtrFor.get();
   myComponentBackward=*compPtrBack.get();*/
}
void AbstractTask::reset(ADB::length_t inS,
                         ADB::length_t outS,
                         ADB::length_t _safetySize,
                         ADB::memPtr inP,
                         ADB::memPtr outP) {
  inStream->higherReset(inP, inS);
  outStream->higherReset(outP, outS);
  safetySize = _safetySize;
  stopPOS = inS;
}
length_t AbstractTask::runForwardTask() {
  length_t endBits = BYTES_TO_BITS(stopPOS);
  while (inStream->readOffset < endBits) {  // printf("%d\r\n",inStream->readOffset);
    number_t i;
    for (i = 0; i < forwardSize(); i++) {
      getForwardComponent(i)->exeFunction();
      getForwardComponent(i)->writeArgFunction();
    }
  }
  return BITS_TO_BYTES(outStream->numberOfBitsUsed);
}
length_t AbstractTask::runBackwardTask() {
  length_t endBits = BYTES_TO_BITS(stopPOS);
  while (inStream->readOffset < endBits) {
    number_t i;
    for (i = 0; i < backwardSize(); i++) {
      getBackwardComponent(i)->exeFunction();
      getBackwardComponent(i)->writeArgFunction();
    }
  }
  return BITS_TO_BYTES(outStream->numberOfBitsUsed);
}
length_t AbstractTask::profileForwardTask() {
  length_t endBits = BYTES_TO_BITS(stopPOS);
  number_t i;
  for (i = 0; i < forwardSize(); i++) {
    getForwardComponent(i)->profileInfo.reset();
  }
  for (i = 0; i < forwardPrepare.size(); i++) {
    forwardPrepare[i]->profileInfo.reset();
  }
  for (i = 0; i < forwardPrepare.size(); i++) {
    tb.runCompExeFunc(forwardPrepare[i]);
  }
  while (inStream->readOffset < endBits) {
    //printf("%d=%d,",inStream->readOffset,endBits);
    for (i = 0; i < forwardSize(); i++) {
      //getForwardComponent(i).exeFunction();
      tb.runCompExeFunc(getForwardComponent(i));
    }
  }
  return BITS_TO_BYTES(outStream->numberOfBitsUsed);
}
length_t AbstractTask::profileBackwardTask() {
  length_t endBits = BYTES_TO_BITS(stopPOS);
  number_t i;
  for (i = 0; i < backwardSize(); i++) {
    getBackwardComponent(i)->profileInfo.reset();
  }
  for (i = 0; i < backwardPrepare.size(); i++) {
    backwardPrepare[i]->profileInfo.reset();
  }
  for (i = 0; i < backwardPrepare.size(); i++) {
    tb.runCompExeFunc(backwardPrepare[i]);
  }
  while (inStream->readOffset < endBits) {
    // printf("%d-%d,%d\r\n",inStream->readOffset,endBits,outStream->numberOfBitsUsed);
    for (i = 0; i < backwardSize(); i++) {
      tb.runCompExeFunc(getBackwardComponent(i));
    }
  }
  return BITS_TO_BYTES(outStream->numberOfBitsUsed);
}
void AbstractTask::printProfile() {
  number_t i;
  //printf("\r\n");
  compProfileInfo_t total;
  total.runTime = 0;
  if (forwardSize() > 0) {
    getForwardComponent(0)->profileInfo.printHead();
  }
  for (i = 0; i < forwardPrepare.size(); i++) {
    string str = forwardPrepare[i]->getName();
    printf("%s:", str.data());
    total = total + forwardPrepare[i]->profileInfo;
    forwardPrepare[i]->profileInfo.printAll();
    printf("\r\n");
  }
  for (i = 0; i < forwardSize(); i++) {
    string str = getForwardComponent(i)->getName();

    printf("%s:", str.data());
    total = total + getForwardComponent(i)->profileInfo;
    getForwardComponent(i)->profileInfo.printAll();
    printf("\r\n");
  }
  printf("totoal:");
  total.printAll();
  printf("\r\n");
}

void AbstractTask::printBackwardProfile() {
  number_t i;
  printf("\r\n");
  compProfileInfo_t total;
  total.runTime = 0;
  if (backwardSize() > 0) {
    getBackwardComponent(0)->profileInfo.printHead();
  }
  for (i = 0; i < backwardPrepare.size(); i++) {
    string str = backwardPrepare[i]->getName();
    printf("%s:", str.data());
    total = total + backwardPrepare[i]->profileInfo;
    backwardPrepare[i]->profileInfo.printAll();
    printf("\r\n");
  }
  for (i = 0; i < backwardSize(); i++) {
    string str = getBackwardComponent(i)->getName();
    //tb.runCompExeFunc(*getBackwardComponent(i).get());
    printf("%s:", str.data());
    total = total + getBackwardComponent(i)->profileInfo;
    getBackwardComponent(i)->profileInfo.printAll();
    printf("\r\n");
    //printf("%s:%ld us\r\n",str.data(),getBackwardComponent(i)->profileInfo.runTime);
  }
  printf("totoal:");
  total.printAll();
  printf("\r\n");
}
/*AbstractTask::AbstractTask(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP)
{
    //inStream =std::make_shared<BitStream>(50, 32);
}*/