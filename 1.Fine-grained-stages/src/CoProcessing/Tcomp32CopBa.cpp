//
// Created by tony on 12/04/22.
//

#include <CoProcessing/Tcomp32CopBa.h>
using namespace ADB;
void Tcomp32CopBaS0::threadMain() {
  shouldStop = false;
  //cout<<"s0 at "+ to_string(cpuBind)+"proces"+ to_string(inIdxBase)+"to"+to_string(inMax)+"\r\n";

  while (1) {
    if (isFirstRun) {
      isFirstRun = false;
    } else {
      headBarrier->arrive_and_wait();
    }
    // cout<<"s0 at "+ to_string(cpuBind)+"proces"+ to_string(batchCnt)+"th batch\r\n";
    outCnt = outIdxBase;
    //creat micro batch
    while (outCnt < outMax) {
      if (!inputQueue->empty()) {
        uint32_t in = *inputQueue->front();
        inputQueue->pop();
        outputBuffer->at(outCnt) = in;

        outCnt++;
        //cout<<"s0 at"+ to_string(cpuBind)+"proces"+ to_string(outCnt)+"\r\n";
      }

    }//end of one batch
    // cout<<"s0 at "+ to_string(cpuBind)+"proces"+ to_string(batchCnt)+"th batch done\r\n";
    // cout<<"s0 at"+ to_string(cpuBind)+"proces"+ to_string(batchCnt)+"th batch done\r\n";
    tailBarrier->arrive_and_wait();
    // tailBarrier->wait()
    if (stopCondition()) {//cout<<"s0 at"+ to_string(cpuBind)+"end\r\n";
      return;
    }
  }

}

void Tcomp32CopBaS1::threadMain() {
  shouldStop = false;
  //cout<<"s1 at "+ to_string(cpuBind)+"proces"+ to_string(inIdxBase)+"to"+to_string(inMax)+"\r\n";
  while (1) {
    headBarrier->arrive_and_wait();
    // cout<<"s1 at "+ to_string(cpuBind)+"proces"+ to_string(batchCnt)+"th batch\r\n";
    outCnt = outIdxBase;
    inCnt = inIdxBase;
    while (outCnt < outMax) {
      uint32_t in = inputBuffer->at(inCnt);

      Tcomp32CopBa_s1S2Info out;
      size_t bits;
      if (in == 0) {
        bits = 1;
      } else {
        bits = 32 - __builtin_clz(in);
      }
      out.value = (in << 5) | (bits - 1);
      out.len = bits + 5;
      outputBuffer->at(outCnt) = out;
      inCnt++;
      outCnt++;
      /*if(cpuBind!=0)
      {
        cout<<"s1 at"+ to_string(cpuBind)+"proces "+ to_string(in)+" at "+ to_string(outCnt) +"\r\n";
      }*/

    }

    // return;
    tailBarrier->arrive_and_wait();
    //cout<<"s1 at "+ to_string(cpuBind)+"proces"+ to_string(batchCnt)+"th batch done\r\n";
    if (stopCondition()) {//cout<<"s1 at"+ to_string(cpuBind)+"end\r\n";
      return;
    }
  }

}

void Tcomp32CopBaS2::threadMain() {
  shouldStop = false;
  outCnt = 0;
  inCnt = 0;
  while (1) {
    headBarrier->arrive_and_wait();
    // cout<<"s2 at "+ to_string(cpuBind)+"proces"+ to_string(batchCnt)+"th batch \r\n";
    inCnt = inIdxBase;
    outCnt = outIdxBase;
    while (outCnt < outMax) {
      Tcomp32CopBa_s1S2Info in = inputBuffer->at(inCnt);
      outStream->writeValue<uint64_t>(in.value, in.len);
      outBits += in.len;
      /*  cout<<"s2 at"+ to_string(cpuBind)+"proces"+ to_string(outCnt)+":"+ to_string(in.value)+","+ \
        to_string(in.len)+","+ to_string(outStream->numberOfBitsUsed)+"\r\n";*/
      inCnt++;
      outCnt++;
    }
    // cout<<"s2 at "+ to_string(cpuBind)+"proces"+ to_string(batchCnt)+"th batch done\r\n";
    if (stopCondition()) {//cout<<"s2 at"+ to_string(cpuBind)+"end\r\n";
      return;
    } else {
      tailBarrier->arrive_and_wait();
    }
  }
}

void Tcomp32CopBa::initThreads(size_t bigCoreWeight,
                               size_t littleCoreWeight,
                               size_t bigCores,
                               size_t littleCores,
                               size_t batchSize) {
  cores = bigCores + littleCores;
  size_t bw = (bigCoreWeight / bigCores);
  if (!bw) {
    bw = 1;
  }
  size_t lw = littleCoreWeight / littleCores;
  if (!lw) {
    lw = 1;
  }
  //init vectors
  s0Threads = vector<Tcomp32CopBaS0Ptr>(cores);
  s1Threads = vector<Tcomp32CopBaS1Ptr>(cores);
  s2Threads = vector<Tcomp32CopBaS2Ptr>(cores);

  s0Rate = vector<size_t>(cores);
  s1Rate = vector<size_t>(cores);
  s2Rate = vector<size_t>(cores);
  splitRate = vector<size_t>(cores);
  //init the buffer
  s01Buffer = make_shared<vector<uint32_t>>(batchSize);
  s12Buffer = make_shared<vector<Tcomp32CopBa_s1S2Info>>(batchSize);
  //init barrier
  s01Bar = std::make_shared<std::barrier<>>(cores * 2);
  s12Bar = std::make_shared<std::barrier<>>(cores * 2);
  s20Bar = std::make_shared<std::barrier<>>(cores * 2);
  //init threads
  for (size_t i = 0; i < cores; i++) {
    s2Threads[i] = make_shared<Tcomp32CopBaS2>();
    s2Threads[i]->setOutputLen(outBufLen);
    s1Threads[i] = make_shared<Tcomp32CopBaS1>();
    s0Threads[i] = make_shared<Tcomp32CopBaS0>();
    s0Threads[i]->setStop(batchCnt);
    s1Threads[i]->setStop(batchCnt);
    s2Threads[i]->setStop(batchCnt);
  }
  //calculate distribution vectors
  size_t fraction = lw * littleCores + bw * bigCores;

  size_t base = 0;
  size_t len = lw * batchSize / fraction;
  for (size_t i = 0; i < littleCores; i++) {
    s0Threads[i]->initInput(base, len, s20Bar, nullptr);
    s0Threads[i]->initOutput(base, len, s01Bar, s01Buffer);
    s0Threads[i]->setBind(LITTLE_CORE_BASE + i);

    s1Threads[i]->initInput(base, len, s01Bar, s01Buffer);
    s1Threads[i]->initOutput(base, len, s12Bar, s12Buffer);
    s1Threads[i]->setBind(LITTLE_CORE_BASE + i);

    s2Threads[i]->initInput(base, len, s12Bar, s12Buffer);
    s2Threads[i]->initOutput(base, len, s20Bar, nullptr);
    s2Threads[i]->setBind(LITTLE_CORE_BASE + i);
    cout << "core" + to_string(LITTLE_CORE_BASE + i) + ", " + to_string(base) + "to" + to_string(base + len) << endl;
    base += len;
    splitRate[i] = base;

  }
  len = bw * batchSize / fraction;
  //big cores
  for (size_t j = 0; j < bigCores; j++) {
    size_t i = j + littleCores;
    if (j == bigCores - 1) {
      len = batchSize - base;
    }
    s0Threads[i]->initInput(base, len, s20Bar, nullptr);
    s0Threads[i]->initOutput(base, len, s01Bar, s01Buffer);
    s0Threads[i]->setBind(BIG_CORE_BASE + j);

    s1Threads[i]->initInput(base, len, s01Bar, s01Buffer);
    s1Threads[i]->initOutput(base, len, s12Bar, s12Buffer);
    s1Threads[i]->setBind(BIG_CORE_BASE + j);

    s2Threads[i]->initInput(base, len, s12Bar, s12Buffer);
    s2Threads[i]->initOutput(base, len, s20Bar, nullptr);
    s2Threads[i]->setBind(BIG_CORE_BASE + j);
    cout << "core" + to_string(BIG_CORE_BASE + j) + ", " + to_string(base) + "to" + to_string(base + len) << endl;
    base += len;
    splitRate[i] = base;

  }
}

void Tcomp32CopBa::initThreads(vector<size_t> bigCoreWeight,
                               vector<size_t> littleCoreWeight,
                               size_t bigCores,
                               size_t littleCores,
                               size_t batchSize) {
  cores = bigCores + littleCores;
  vector<size_t> bw(3);
  vector<size_t> lw(3);
  for (size_t i = 0; i < 3; i++) {
    bw[i] = (bigCoreWeight[i] / bigCores);
    lw[i] = (littleCoreWeight[i]) / littleCores;
    if (!bw[i]) {
      bw[i] = 1;
    }
    if (!lw[i]) {
      lw[i] = 1;
    }
  }

  //init vectors
  s0Threads = vector<Tcomp32CopBaS0Ptr>(cores);
  s1Threads = vector<Tcomp32CopBaS1Ptr>(cores);
  s2Threads = vector<Tcomp32CopBaS2Ptr>(cores);

  s0Rate = vector<size_t>(cores);
  s1Rate = vector<size_t>(cores);
  s2Rate = vector<size_t>(cores);
  splitRate = vector<size_t>(cores);
  //init the buffer
  s01Buffer = make_shared<vector<uint32_t>>(batchSize);
  s12Buffer = make_shared<vector<Tcomp32CopBa_s1S2Info>>(batchSize);
  //init barrier
  s01Bar = std::make_shared<std::barrier<>>(cores * 2);
  s12Bar = std::make_shared<std::barrier<>>(cores * 2);
  s20Bar = std::make_shared<std::barrier<>>(cores * 2);
  //init threads
  for (size_t i = 0; i < cores; i++) {
    s2Threads[i] = make_shared<Tcomp32CopBaS2>();
    s2Threads[i]->setOutputLen(outBufLen);
    s1Threads[i] = make_shared<Tcomp32CopBaS1>();
    s0Threads[i] = make_shared<Tcomp32CopBaS0>();
    s0Threads[i]->setStop(batchCnt);
    s1Threads[i]->setStop(batchCnt);
    s2Threads[i]->setStop(batchCnt);
  }
  //calculate distribution vectors
  vector<size_t> fraction(3);
  vector<size_t> len(3);
  vector<size_t> base(3);
  for (size_t i = 0; i < 3; i++) {
    fraction[i] = lw[i] * littleCores + bw[i] * bigCores;
    base[i] = 0;
    len[i] = lw[i] * batchSize / fraction[i];
  }
  for (size_t i = 0; i < littleCores; i++) {
    s0Threads[i]->initInput(base[0], len[0], s20Bar, nullptr);
    s0Threads[i]->initOutput(base[0], len[0], s01Bar, s01Buffer);
    s0Threads[i]->setBind(LITTLE_CORE_BASE + i);

    s1Threads[i]->initInput(base[1], len[1], s01Bar, s01Buffer);
    s1Threads[i]->initOutput(base[1], len[1], s12Bar, s12Buffer);
    s1Threads[i]->setBind(LITTLE_CORE_BASE + i);

    s2Threads[i]->initInput(base[2], len[2], s12Bar, s12Buffer);
    s2Threads[i]->initOutput(base[2], len[2], s20Bar, nullptr);
    s2Threads[i]->setBind(LITTLE_CORE_BASE + i);
    for (size_t s = 0; s < 3; s++) {
      cout << "core" + to_string(LITTLE_CORE_BASE + i) + ", s" + to_string(s) + "," + to_string(base[s]) + "to"
          + to_string(base[s] + len[s]) << endl;
      base[s] += len[s];
    }
    splitRate[i] = base[0];
  }
  for (size_t i = 0; i < 3; i++) {
    len[i] = bw[i] * batchSize / fraction[i];
  }
  //big cores
  for (size_t j = 0; j < bigCores; j++) {
    size_t i = j + littleCores;
    if (j == bigCores - 1) {
      //len=batchSize-base;
      for (size_t s = 0; s < 3; s++) {
        len[s] = batchSize - base[s];
      }
    }
    s0Threads[i]->initInput(base[0], len[0], s20Bar, nullptr);
    s0Threads[i]->initOutput(base[0], len[0], s01Bar, s01Buffer);
    s0Threads[i]->setBind(BIG_CORE_BASE + j);

    s1Threads[i]->initInput(base[1], len[1], s01Bar, s01Buffer);
    s1Threads[i]->initOutput(base[1], len[1], s12Bar, s12Buffer);
    s1Threads[i]->setBind(BIG_CORE_BASE + j);

    s2Threads[i]->initInput(base[2], len[2], s12Bar, s12Buffer);
    s2Threads[i]->initOutput(base[2], len[2], s20Bar, nullptr);
    s2Threads[i]->setBind(BIG_CORE_BASE + j);
    for (size_t s = 0; s < 3; s++) {
      cout << "core" + to_string(BIG_CORE_BASE + j) + ", s" + to_string(s) + "," + to_string(base[s]) + "to"
          + to_string(base[s] + len[s]) << endl;
      base[s] += len[s];
    }
    // cout<<"core"+ to_string(BIG_CORE_BASE+j)+", "+ to_string(base)+"to"+to_string(base+len)<<endl;
    //base+=len;
    splitRate[i] = base[0];

  }
}
void Tcomp32CopBa::run() {
  for (size_t i = 0; i < cores; i++) {
    s0Threads[i]->start();
    s1Threads[i]->start();
    s2Threads[i]->start();
  }
}
void Tcomp32CopBa::stop() {
  /*for(size_t i=0;i<cores;i++)
  {

  }*/
  for (size_t i = 0; i < cores; i++) {
    s0Threads[i]->join();
    s1Threads[i]->join();
    s2Threads[i]->join();
  }
}
void Tcomp32CopBa::inputData(uint32_t da) {
  s0Threads[splitIdx]->inputData(da);
  splitCnt++;
  if (splitCnt >= splitRate[splitIdx]) {
    splitIdx++;
  }
  if (splitIdx == cores) {
    splitIdx = 0;
    splitCnt = 0;
  }
}
