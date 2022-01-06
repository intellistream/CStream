#ifndef ADB_INCLUDE_COMPRESSIONTASKS_TCOMP32TASK_HPP_
#define ADB_INCLUDE_COMPRESSIONTASKS_TCOMP32TASK_HPP_
#include <CommonData/CommonData.hpp>
#include <CompressionTasks/AbstractTask.hpp>
#include <Utils/MemAddresser.hpp>
#include <vector>
#include <Utils/TimeTestBench.hpp>
using namespace std;
namespace ADB {

class Tcomp32Task : public AbstractTask {
 private:
  /* data */
 public:
  Tcomp32Task(/* args */);
  ~Tcomp32Task();
  Tcomp32Task(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
};
typedef std::shared_ptr<Tcomp32Task> Tcomp32TaskPtr;
}
#endif