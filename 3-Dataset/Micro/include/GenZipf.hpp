#ifndef _GENZIPF_HPP_
#define _GENZIPF_HPP_
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
namespace ZIPF {
class GenZipf {
 private:
  /* data */
  vector<double> zipfInline;
  vector<double> lut;
  vector<uint64_t> alphabet;
  double factor, entropy;
  uint64_t alen;
  void gen_alphabet();
  void gen_zipf_lut();
  double freqMax;
 public:
  double getEntropy() {
    return entropy;
  }
  double getMaxFreq() {
    return freqMax;
  }
  // the factor and the alphbet len
  GenZipf(double _factor, uint64_t _alen) {
    factor = _factor;
    alen = _alen;
    gen_alphabet();
    gen_zipf_lut();
  }
  template<typename puType>
  vector<puType> outPutArray(uint64_t len) {
    vector<puType> ret(len);
    for (uint64_t i = 0; i < len; i++) {
      /* take random number */
      double r = ((double) rand()) / RAND_MAX;

      /* binary search in lookup table to determine item */
      uint64_t left = 0;
      uint64_t right = alen - 1;
      uint64_t m;       /* middle between left and right */
      uint64_t pos;     /* position to take */

      if (lut[0] >= r)
        pos = 0;
      else {
        while (right - left > 1) {
          m = (left + right) / 2;

          if (lut[m] < r)
            left = m;
          else
            right = m;
        }

        pos = right;
      }

//        /* uint32_t * dst = (uint32_t *)&ret[i]; */
//        tuple_t * dst = (tuple_t *) &ret[i];
//        dst->key = (intkey_t)alphabet[pos];
//        /* ret[i] = alphabet[pos]; */
      ret[i] = (puType) alphabet[pos];
    }

    return ret;
  }
  ~GenZipf() {

  }
};
void genZipf32Csv(char *fname, double factor, uint64_t range, uint64_t times);
void genZipf64Csv(char *fname, double factor, uint64_t range, uint64_t times);
void genZipf64Bin(char *fname, double factor, uint64_t range, uint64_t times);
void genZipf32Bin(char *fname, double factor, uint64_t range, uint64_t times);
void genZipfFloatBin(char *fname, double factor, uint64_t range, uint64_t times);
}

#endif