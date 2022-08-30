//
// Created by tony on 18/04/22.
//

#include <CoProcessing/Tdic32CopBa.h>
#include <Utils/MTSBHashTable.h>
//preprocess
void Tdic32CopBaS1::threadMain() {
  shouldStop = false;
  //cout<<"s1 at "+ to_string(cpuBind)+"proces"+ to_string(inIdxBase)+"to"+to_string(inMax)+"\r\n";
  while (1) {
    headBarrier->arrive_and_wait();
    // cout<<"s1 at "+ to_string(cpuBind)+"proces"+ to_string(batchCnt)+"th batch\r\n";
    outCnt = outIdxBase;
    inCnt = inIdxBase;
    while (outCnt < outMax) {
      uint32_t in = inputBuffer->at(inCnt);
      outputBuffer->at(outCnt) = MTSBHashTable::mtsb_hash(in,TDIC32_USE_HASHBITS);
      inCnt++;
      outCnt++;
    }
    tailBarrier->arrive_and_wait();
    if (stopCondition()) {//cout<<"s1 at"+ to_string(cpuBind)+"end\r\n";
      return;
    }
  }

}
//state update
void Tdic32CopBaS2::initState() {
  uint32_t i;
  for (i = 0; i < TDIC32_USE_HASHENTRIES; i++) {
    tb[i].value = 0xffffffff;
  }
  tb[MTSBHashTable::mtsb_hash(0xffffffff,TDIC32_USE_HASHBITS)].value = 0;
}