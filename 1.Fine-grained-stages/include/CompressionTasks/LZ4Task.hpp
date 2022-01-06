#ifndef ADB_INCLUDE_COMPRESSIONTASKS_LZ4Task_HPP_
#define ADB_INCLUDE_COMPRESSIONTASKS_LZ4Task_HPP_
#include <CommonData/CommonData.hpp>
#include <CompressionTasks/AbstractTask.hpp>
#include <Utils/MemAddresser.hpp>
#include <vector>
#include <Utils/TimeTestBench.hpp>
#include <CompressionComponents/LZ4Components.hpp>
using namespace std;
namespace ADB {

class LZ4Task : public AbstractTask {
 private:
  /* data */
 public:
  LZ4Task(/* args */);
  ~LZ4Task();
  LZ4Args *myLz4Arg;
  void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  LZ4Task(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
};
typedef std::shared_ptr<LZ4Task> LZ4TaskPtr;
}
#endif