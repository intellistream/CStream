#ifndef ADB_INCLUDE_PARTITIONRUNNERS_TDIC32PARTITIONRUNNERS_HPP_
#define ADB_INCLUDE_PARTITIONRUNNERS_TDIC32PARTITIONRUNNERS_HPP_
#include <PartitionRunners/AbstractPartitionRunner.hpp>
using namespace ADB;

namespace ADB {
/*class:Tdic32PPUnit
description: The class of a parallel units in a tdic32 partition runner

date:20211121
*/
class Tdic32PPUnit : public AbstractPPUnit {
 protected:
  void puFunction();
 public:
  // Tdic32PPUnit();

  Tdic32PPUnit(ADB::memPtr inP, length_t startByte, length_t length, length_t safeSize);
  ~Tdic32PPUnit() {}
  double getIpm() {
    return getinLineIpm(mySrcLen);
  }
};
typedef std::shared_ptr<Tdic32PPUnit> Tdic32PPUnitPtr;
/*class:Tdic32PartitionRunner
description: The class of a whole tdic32 job

date:202001015
*/
class Tdic32PartitionRunner : public AbstractPartitionRunner {
 private:
  /* data */

 public:
  void establishPPUnits();
  void collectResults();
  Tdic32PartitionRunner(/* args */);
  ~Tdic32PartitionRunner();
  Tdic32PartitionRunner(ADB::length_t inS,
                         ADB::length_t outS,
                         ADB::length_t safetySize,
                         ADB::memPtr inP,
                         ADB::memPtr outP);
  double getIpmOfCollection() {
    return myPerf2.getIpm(inS / 2);
  }
};
typedef std::shared_ptr<Tdic32PartitionRunner> Tdic32PartitionRunnerPtr;
}

#endif