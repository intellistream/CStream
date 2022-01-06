#ifndef ADB_INCLUDE_COMPRESSIONTASKS_MRLETask_HPP_
#define ADB_INCLUDE_COMPRESSIONTASKS_MRLETask_HPP_
#include <CommonData/CommonData.hpp>
#include <CompressionTasks/AbstractTask.hpp>
#include <Utils/MemAddresser.hpp>
#include <vector>
#include <Utils/TimeTestBench.hpp>
#include <CompressionComponents/MRLEComponents.hpp>
using namespace std;
namespace ADB {

class MRLETask : public AbstractTask {
 private:
  /* data */
 public:
  MRLETask(/* args */);
  ~MRLETask();
  MRLEArgs *myMrleArg;
  void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  MRLETask(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
};

}
#endif