#include <stdio.h>
#include <stdlib.h>

#include <string.h>
/*#include <GenRand.h>
#include <Duplicate.h>
#include <GenGaussian.h>*/
#include <GenZipf.hpp>
using namespace ZIPF;
int main(int argc, char *argv[]) {

  uint64_t len32 = 9328000 / (sizeof(uint32_t));
  uint64_t len64 = 9328000 / (sizeof(uint64_t));
  //vocabulary
  genZipf64Bin("v_0.bin", 0, 400, len64);
  genZipf64Bin("v_05.bin", 0.5, 400, len64);
  genZipf64Bin("v_1.bin", 1, 400, len64);
  genZipf64Bin("v_2.bin", 2, 400, len64);
  //entropy
  genZipf32Bin("e_0.bin", 0, 500, len32);
  genZipf32Bin("e_05.bin", 0.5, 500, len32);
  genZipf32Bin("e_1.bin", 1, 500, len32);
  genZipf32Bin("e_2.bin", 2, 500, len32);
  //range
  genZipf32Bin("r_0.bin", 0, 500, len32);
  genZipf32Bin("r_05.bin", 0, 5000, len32);
  genZipf32Bin("r_1.bin", 0, 50000, len32);
  genZipf32Bin("r_2.bin", 0, 500000, len32);

  return 0;
}