#include <PartitionRunners/AbstractPartitionRunner.hpp>

using namespace ADB;
AbstractPPUnit::AbstractPPUnit(ADB::memPtr inP, length_t startByte, length_t len, length_t safeSize) {

  memPtr tin = &inP[startByte];
  //ADB_memcpy(midInput.get(), tin, len);
  pSrc = tin;
  mySrcLen = len;
  mySafeSize = safeSize;
  midResult = std::shared_ptr<ADB::memCeil_t>(new ADB::memCeil_t[mySafeSize],
                                              [](ADB::memCeil_t *p) {
                                                delete[] p;
                                              });

  /* inStream = make_shared<MemAddresser>(tin, endByte-startByte+1);
   outStream= make_shared<MemAddresser>(midResult.get(), safeSize);*/

}
AbstractPartitionRunner::AbstractPartitionRunner(/* args */) {
  partitions = std::thread::hardware_concurrency();
}

AbstractPartitionRunner::~AbstractPartitionRunner() {
}

AbstractPartitionRunner::AbstractPartitionRunner(ADB::length_t _inS,
                                                 ADB::length_t _outS,
                                                 ADB::length_t _safetySize,
                                                 ADB::memPtr _inP,
                                                 ADB::memPtr _outP) {
  inS = _inS;
  outS = _outS;
  inP = _inP;
  outP = _outP;
  safetySize = _safetySize;
  partitions = std::thread::hardware_concurrency();
  setUpMeter();
}
void AbstractPartitionRunner::resetPartitions(length_t n) {
  if (n > std::thread::hardware_concurrency()) {
    ADB_FATAL_ERROR("can not setup so many partitions");
    partitions = std::thread::hardware_concurrency();
  } else {
    partitions = n;
  }

}
void AbstractPartitionRunner::execute() {
  struct timeval tstart, tend;
  subName = "para_units";
  myPerf = ThreadPerf(mainCpu);
  myPerf2 = ThreadPerf(mainCpu);
  if (powerMeter) {
    powerMeter->startMeter();
  }
  gettimeofday(&tstart, NULL);
  //real code here
  inlineEstablishPPU();
  for (size_t i = 0; i < pus.size(); i++) {
    pus[i]->start();
  }
  for (size_t i = 0; i < pus.size(); i++) {
    pus[i]->join();
  }
  inlineCollectResults();

  gettimeofday(&tend, NULL);
  if (powerMeter) {
    powerMeter->stopMeter();
  }
  allRunTime = UtilityFunctions::getRunningUs(tstart, tend);
}

void AbstractPartitionRunner::seqProfile() {
  struct timeval tstart, tend;
  subName = "seq_units";
  if (powerMeter) {
    powerMeter->startMeter();
  }
  gettimeofday(&tstart, NULL);
  //real code here
  inlineEstablishPPU();
  for (size_t i = 0; i < pus.size(); i++) {
    pus[i]->start();
    pus[i]->join();
  }

  inlineCollectResults();

  gettimeofday(&tend, NULL);
  if (powerMeter) {
    powerMeter->stopMeter();
  }
  allRunTime = UtilityFunctions::getRunningUs(tstart, tend);
}
void AbstractPartitionRunner::printStages() {
  string perfHead = pus[0]->headStringPrintf();
  string perfMid;
  printf("uuid\t|cpu\t|name\t|latency\t|partSize\t|energy\t|peakPower\t%s", perfHead.data());
  printf("%lx\t|%lx\t|partition\t|%ld\t|%ld\t|NA\t|NA\t%s",
         (length_t) this,
         mainCpu,
         establishTime,
         inS,
         perfHead.data());

  for (size_t i = 0; i < pus.size(); i++) {
    AbstractPPUnitPtr pp = pus[i];
    perfMid = pp->resultStringPrintf();
    printf("%lx\t|%ld\t|%s%d\t|%ld\t|%ld\t|NA\t|NA\t%s",
           pp->getId(),
           pp->getCpu(),
           pp->getName().data(),
           i,
           pp->getRunTime(),
           pp->getSrcLen(),
           perfMid.data());
  }
  printf("%lx\t|%lx\t|collection\t|%ld\t|%ld\t|NA\t|NA\t%s",
         (length_t) this,
         mainCpu,
         collectTime,
         inS,
         perfHead.data());
  if (powerMeter) {
    printf("\t|NA\t|%s-total\t|%ld\t|%ld\t|%lf\t|%lf\t%s",
           subName.data(),
           allRunTime,
           inS,
           powerMeter->getE(),
           powerMeter->getPeak(),
           perfHead.data());
  } else {
    printf("NA\t|NA\t|%s-total\t|%ld\t|%ld\t|NA\t|NA\t%s", subName.data(), allRunTime, inS, perfHead.data());
  }

}

void AbstractPartitionRunner::outputStages2Csv(std::string fname) {
  string perfHead = pus[0]->headStringCsv();
  string perfMid;
  FILE *fp = fopen((char *) fname.data(), "w");
  if (!fp) {
    ADB_FATAL_ERROR("Can not creat csv");
    return;
  }
  fprintf(fp, "uuid,cpu,name,latency,partSize,enery,peakPower,IPM%s", perfHead.data());
  fprintf(fp,
          "%lx,%lx,partition,%ld,%ld,NA,NA,%lf%s",
          (length_t) this,
          mainCpu,
          establishTime,
          inS,
          getIpmOfEstablish(),
          myPerf.resultStringCsv().data());

  for (size_t i = 0; i < pus.size(); i++) {
    AbstractPPUnitPtr pp = pus[i];
    perfMid = pp->resultStringCsv();
    fprintf(fp,
            "%lx,%ld,%s%d,%ld,%ld,NA,NA,%lf%s",
            pp->getId(),
            pp->getCpu(),
            pp->getName().data(),
            i,
            pp->getRunTime(),
            pp->getSrcLen(),
            pp->getIpm(),
            perfMid.data());
  }
  fprintf(fp,
          "%lx,%lx,collection,%ld,%ld,NA,NA,%lf%s",
          (length_t) this,
          mainCpu,
          collectTime,
          inS,
          getIpmOfCollection(),
          myPerf2.resultStringCsv().data());
  if (powerMeter) {
    fprintf(fp,
            "NA,NA,%s-total,%ld,%ld,%lf,%lf,NA%s",
            subName.data(),
            allRunTime,
            inS,
            powerMeter->getE(),
            powerMeter->getPeak(),
            perfHead.data());
  } else {
    fprintf(fp, "NA,NA,%s-total,%ld,%ld,NA,NA%s", subName.data(), allRunTime, inS, perfHead.data());
  }

  fclose(fp);
}
void AbstractPartitionRunner::setPartitionVector(std::vector<int> pv) {
  if (pv.size() < 1) {
    ADB_FATAL_ERROR("invaild partition vector, too small");
    return;
  }
  length_t par0 = pv[0];
  if (par0 > std::thread::hardware_concurrency()) {
    ADB_FATAL_ERROR("invaild partition vector, too many partitions");
    return;
  }
  if (pv.size() < 1 + 2 * par0) {
    ADB_FATAL_ERROR("invaild partition vector,run size");
  }

  for (size_t i = 1 + par0; i < pv.size(); i++) {
    if (pv[0] < 0) {
      ADB_FATAL_ERROR("invaild partition vector,negative weight");
      return;
    }
  }
  partitionRemap = std::vector<int>(pv.begin() + 1, pv.begin() + par0 + 1);
  partitionWeight = std::vector<int>(pv.begin() + par0 + 1, pv.end());
  printf("remap:");
  for (size_t i = 0; i < partitionRemap.size(); i++) {
    printf("%d,", partitionRemap[i]);
  }

  printf("\r\nweights:");
  for (size_t i = 0; i < partitionWeight.size(); i++) {
    printf("%d,", partitionWeight[i]);
  }
  //partitionVec=pv;
  ADB_INFO("successful in setting partition vector");
  return;

}