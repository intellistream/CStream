//
// Created by tony on 18/04/22.
//

#ifndef ALIANCEDB_INCLUDE_COPROCESSING_TDIC32COPBA_H_
#define ALIANCEDB_INCLUDE_COPROCESSING_TDIC32COPBA_H_
#include <Utils/MultiCore/AbstractThread.hpp>
#include <Utils/MultiCore/SafeQueue.hpp>
#include <Utils/MultiCore/SPSCQueue.hpp>
#include <Utils/MemAddresser.hpp>
#include <CommonData/CommonData.hpp>
#include <CoProcessing/Tcomp32CopBa.h>
#include <MeterHelp.hpp>
#include <vector>
#include <mutex>
using namespace std;
namespace ADB {
#define  TDIC32_USE_HASHBITS 11
#define TDIC32_USE_HASHENTRIES (1 <<TDIC32_USE_HASHBITS )
class Tdic32CopBaS1 : public AbstractThread, public Tcomp32CopBaStep<Tcomp32CopBa_s0OutPtr, Tcomp32CopBa_s0OutPtr> {
 public:
  Tdic32CopBaS1() {}
  ~Tdic32CopBaS1() {}
 protected:
  void threadMain();
};
class Tdic32CopBaS2_privateState{
 public:
  uint32_t value;
  uint32_t offset;
  Tdic32CopBaS2_privateState(){}
  ~Tdic32CopBaS2_privateState(){}
};
class Tdic32CopBaS2 : public AbstractThread, public Tcomp32CopBaStep<Tcomp32CopBa_s0OutPtr, Tcomp32CopBa_s1OutPtr> {
 public:
  void initState();
  Tdic32CopBaS2() {initState();

  }
  ~Tdic32CopBaS2() {}
  Tcomp32CopBa_s0OutPtr rawValueInput;
  void setRawValue(Tcomp32CopBa_s0OutPtr _raw)
  {
    rawValueInput=_raw;
  }
 protected:
  void threadMain();
  Tdic32CopBaS2_privateState tb[TDIC32_USE_HASHENTRIES];
};
//default no state sharing
class Tdic32CopBa {

};
}
#endif //ALIANCEDB_INCLUDE_COPROCESSING_TDIC32COPBA_H_
