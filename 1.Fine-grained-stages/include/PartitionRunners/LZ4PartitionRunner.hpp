#ifndef ADB_INCLUDE_PARTITIONRUNNERS_LZ4PARTITIONRUNNERS_HPP_
#define ADB_INCLUDE_PARTITIONRUNNERS_LZ4ARTITIONRUNNERS_HPP_
#include <PartitionRunners/AbstractPartitionRunner.hpp>
using namespace ADB;

namespace ADB {
/*class:LZ4PPUnit
description: The class of a parallel units in a LZ4 partition runner

date:202001019
*/
class LZ4PPUnit : public AbstractPPUnit {
 protected:
  void puFunction();
 public:
  // LZ4PPUnit();

  LZ4PPUnit(ADB::memPtr inP, length_t startByte, length_t length, length_t safeSize);
  ~LZ4PPUnit() {}
  double getIpm() {
    return getinLineIpm(mySrcLen * 3); //load and remap->2, write-1
  }
};
typedef std::shared_ptr<LZ4PPUnit> LZ4PPUnitPtr;
/*class:LZ4PartitionRunner
description: The class of a whole LZ4 job

date:202001019
*/
class LZ4PartitionRunner : public AbstractPartitionRunner {
 private:
  /* data */

 public:
  void establishPPUnits();
  void collectResults();
  LZ4PartitionRunner(/* args */);
  ~LZ4PartitionRunner();
  LZ4PartitionRunner(ADB::length_t inS,
                     ADB::length_t outS,
                     ADB::length_t safetySize,
                     ADB::memPtr inP,
                     ADB::memPtr outP);
  double getIpmOfCollection() {
    return myPerf2.getIpm(inS);
  }

};
typedef std::shared_ptr<LZ4PartitionRunner> LZ4PartitionRunnerPtr;
}

#endif