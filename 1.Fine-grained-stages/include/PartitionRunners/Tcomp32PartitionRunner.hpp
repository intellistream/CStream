#ifndef ADB_INCLUDE_PARTITIONRUNNERS_TCOMP32PARTITIONRUNNERS_HPP_
#define ADB_INCLUDE_PARTITIONRUNNERS_TCOMP32PARTITIONRUNNERS_HPP_
#include <PartitionRunners/AbstractPartitionRunner.hpp>
using namespace ADB;

namespace ADB {
/*class:Tcomp32PPUnit
description: The class of a parallel units in a tcomp32 partition runner

date:202001015
*/
class Tcomp32PPUnit : public AbstractPPUnit {
 protected:
  void puFunction();
 public:
  // Tcomp32PPUnit();

  Tcomp32PPUnit(ADB::memPtr inP, length_t startByte, length_t length, length_t safeSize);
  ~Tcomp32PPUnit() {}
  double getIpm() {
    return getinLineIpm(mySrcLen * 3 / 4);
  }
};
typedef std::shared_ptr<Tcomp32PPUnit> Tcomp32PPUnitPtr;
/*class:Tcomp32PartitionRunner
description: The class of a whole tcomp32 job

date:202001015
*/
class Tcomp32PartitionRunner : public AbstractPartitionRunner {
 private:
  /* data */

 public:
  void establishPPUnits();
  void collectResults();
  Tcomp32PartitionRunner(/* args */);
  ~Tcomp32PartitionRunner();
  Tcomp32PartitionRunner(ADB::length_t inS,
                         ADB::length_t outS,
                         ADB::length_t safetySize,
                         ADB::memPtr inP,
                         ADB::memPtr outP);
  double getIpmOfCollection() {
    return myPerf2.getIpm(inS / 2);
  }
};
typedef std::shared_ptr<Tcomp32PartitionRunner> Tcomp32PartitionRunnerPtr;
}

#endif