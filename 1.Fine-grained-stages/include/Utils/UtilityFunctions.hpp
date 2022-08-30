// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

#ifndef ADB_SRC_UTILS_UTILITYFUNCTIONS_HPP_
#define ADB_SRC_UTILS_UTILITYFUNCTIONS_HPP_
#include <string>
#include <experimental/filesystem>
#include <barrier>
#include <functional>
/* Period parameters */

#define TRUE 1
#define FALSE 0

namespace ADB {
typedef std::shared_ptr<std::barrier<>> BarrierPtr;

class UtilityFunctions {

 public:
  UtilityFunctions();
  static void init_genrand(unsigned long s);
  static double genrand_real3();
  static long genrand_int31(void);
  static unsigned long genrand_int32(void);
  static int64_t getRunningUs(struct timeval tstart, struct timeval tend);

  static std::shared_ptr<std::barrier<>> createBarrier(int count);
  static std::vector<int> getIntVectorFromFile(std::string fname);
};
}
#endif //ADB_SRC_UTILS_UTILITYFUNCTIONS_HPP_
