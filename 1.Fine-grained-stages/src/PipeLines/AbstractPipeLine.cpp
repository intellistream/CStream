#include <PipeLines/AbstractPipeLine.hpp>
#include <Utils/UtilityFunctions.hpp>
using namespace ADB;
using namespace DIVERSE_METER;
AbstractPipeLineStage::AbstractPipeLineStage(length_t cpu, QueueStagePtr _inputQueue, QueueStagePtr _outputQueue) :
    AbstractThread() {
  setBind(cpu);
  inputQueue = _inputQueue;
  outputQueue = _outputQueue;
  //myBarrier=nullptr;
  stageNo = 0;
  stageCnt = 0;
  isLoaded = false;
  hasPrevStage = (_inputQueue != nullptr);
  hasNextStage = (_outputQueue != nullptr);
}
AbstractPipeLineStage::AbstractPipeLineStage(length_t cpu,
                                             bool _hasNextStage,
                                             AbstractPipeLineStagePtr prev,
                                             length_t _ownQueSize) {
  setBind(cpu);
  //auto creat later
  inputQueue = nullptr;
  outputQueue = nullptr;
  hasPrevStage = (prev != nullptr);
  hasNextStage = _hasNextStage;
  prevStage = prev;
  ownQueSize = _ownQueSize;

}
void AbstractPipeLineStage::autoFixQueue() {
  if (hasPrevStage && (!inputQueue)) {
    printf("fix input que for %s\r\n", this->getName().data());
    inputQueue = prevStage->outputQueue;
  }
  if (hasNextStage && (!outputQueue)) {
    printf("fix output que for %s\r\n", this->getName().data());

    int i = checkCpuBind(cpuBind);
    bind2Cpu(i);
    printf("switch to core %d:%d\r\n", cpuBind, i);
    outputQueue = make_shared<rigtorp::SPSCQueue<StageParseArgs >>(ownQueSize);
  }
}
bool AbstractPipeLineStage::shouldLoop() {
  return false;
}
void AbstractPipeLineStage::threadMain() {

  // pipeLineFunction();
  //printf("begin\r\n");
  /*if(!isLoaded)
  {
    stageCnt++;
  }*/
  if (hasNextStage && (!outputQueue)) {//printf("fix output que for %s\r\n",this->getName().data());
    outputQueue = make_shared<rigtorp::SPSCQueue<StageParseArgs >>(ownQueSize);
  }
  waitInitBar();
  if (hasPrevStage && (!inputQueue)) { // printf("fix input que for %s\r\n",this->getName().data());
    inputQueue = prevStage->outputQueue;
  }
  pipeLineInit();

  while (shouldLoop()) {
    if (hasPrevStage) //not the first stage
    {
      if(inputQueue->empty())
      {
        inputQueue->waitForSource();
      }
      while (!inputQueue->empty()) {
        midArg = *inputQueue->front();
        inputQueue->pop();
        pipeLineFunction();
        if (hasNextStage) {
          outputQueue->push(midArg);
          outputQueue->wakeUpSink();
        }
      }
    } else {
      pipeLineFunction();
      if (hasNextStage) {
        outputQueue->push(midArg);
        outputQueue->wakeUpSink();
      }
    }

  }

}

void AbstractPipeLineStage::pipeLineFunction() {

}
AbstractPipeLine::AbstractPipeLine() {

}
AbstractPipeLine::~AbstractPipeLine() {

}

AbstractPipeLine::AbstractPipeLine(ADB::length_t inS,
                                   ADB::length_t outS,
                                   ADB::length_t _safetySize,
                                   ADB::memPtr inP,
                                   ADB::memPtr outP) {
  inStream = make_shared<MemAddresser>(inP, inS);
  outStream = make_shared<MemAddresser>(outP, outS);
  safetySize = _safetySize;
  stopPOS = inS;
//  powerMeter = newEnergyMeter();
}
void AbstractPipeLine::creatQueues() {
  AbstractPipeLineStagePtr spr;

  for (size_t i = 0; i < stages.size(); i++) {
    spr = stages[i];
    spr->autoFixQueue();
  }
}
void AbstractPipeLine::execute() {
  struct timeval tstart, tend;
  //creatQueues();
  makeBarrier();

  for (size_t i = 0; i < stages.size(); i++) {
    stages[i]->setInitBar(initBar);
  }
  if (powerMeter) {
    powerMeter->startMeter();
  }
  gettimeofday(&tstart, NULL);

  for (size_t i = 0; i < stages.size(); i++) {
    stages[i]->start();
  }
  for (size_t i = 0; i < stages.size(); i++) {
    stages[i]->join();
  }
  gettimeofday(&tend, NULL);
  if (powerMeter) {
    powerMeter->stopMeter();
  }
  allRunTime = UtilityFunctions::getRunningUs(tstart, tend);
  subName = "para_all";
}
void AbstractPipeLine::seqProfile() {
  struct timeval tstart, tend;
  //creatQueues();
  if (powerMeter) {
    powerMeter->startMeter();
  }
  gettimeofday(&tstart, NULL);

  for (size_t i = 0; i < stages.size(); i++) {
    stages[i]->start();
    stages[i]->join();
  }
  gettimeofday(&tend, NULL);
  if (powerMeter) {
    powerMeter->stopMeter();
  }
  allRunTime = UtilityFunctions::getRunningUs(tstart, tend);
  subName = "seq_all";
}
void AbstractPipeLine::printStages() {
  string perfHead = stages[0]->headStringPrintf();
  string perfMid;
  printf("uuid\t|cpu\t|name\t|latency\t|energy\t|peakPower\t%s", perfHead.data());
  for (size_t i = 0; i < stages.size(); i++) {
    AbstractPipeLineStagePtr sp = stages[i];
    string str = sp->getName();
    perfMid = sp->resultStringPrintf();
    printf("%lx\t|%ld\t|%s\t|%ld\t|NA\t|NA\t%s",
           sp->getId(),
           sp->getCpu(),
           str.data(),
           sp->getRunTime(),
           perfMid.data());
  }
  if (powerMeter) {
    printf("NA\t|NA\t|%s\t|%ld\t|%lf\t|%lf\t%s",
           subName.data(),
           allRunTime,
           powerMeter->getE(),
           powerMeter->getPeak(),
           perfHead.data());
  } else {
    printf("NA\t|NA\t|%s\t|%ld\t|NA\t|NA\t%s", subName.data(), allRunTime, perfHead.data());
  }

}
void AbstractPipeLine::rebindByVector(std::vector<int> rmv) {
  if (rmv.size() < stages.size()) {
    ADB_INFO("no valid rebind");
    return;
  }
  for (size_t i = 0; i < stages.size(); i++) {
    stages[i]->setCpu(rmv[i]);
  }
}
void AbstractPipeLine::outputStages2Csv(std::string fname) {
  string perfHead = stages[0]->headStringCsv();
  string perfMid;
  FILE *fp = fopen((char *) fname.data(), "w");
  if (!fp) {
    ADB_FATAL_ERROR("Can not creat csv");
    return;
  }
  fprintf(fp, "uuid,cpu,name,latency,energy,peakPower,IPM%s", perfHead.data());
  for (size_t i = 0; i < stages.size(); i++) {
    AbstractPipeLineStagePtr sp = stages[i];
    string str = sp->getName();
    perfMid = sp->resultStringCsv();
    fprintf(fp,
            "%lx,%ld,%s,%ld,NA,NA,%lf%s",
            sp->getId(),
            sp->getCpu(),
            str.data(),
            sp->getRunTime(),
            sp->getIpm(),
            perfMid.data());
  }
  if (powerMeter) {
    fprintf(fp,
            "NA,NA,%s,%ld,%lf,%lf,NA%s",
            subName.data(),
            allRunTime,
            powerMeter->getE(),
            powerMeter->getPeak(),
            perfHead.data());
  } else {

    fprintf(fp, "NA,NA,%s,%ld,NA,NA,NA%s", subName.data(), allRunTime, perfHead.data());
  }

  fclose(fp);
}
void AbstractPipeLine::setUpMeter() {
  powerMeter = newEnergyMeter();
}