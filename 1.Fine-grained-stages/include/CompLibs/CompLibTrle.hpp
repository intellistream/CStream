#ifndef _USER_COMPLIB_TRLE_HPP_
#define _USER_COMPLIB_TRLE_HPP_
#include <CompressionQuery/CompressionQuery.hpp>
namespace ADB {
/*class:CompLibTrle
    description: container of turobo RLE algorithm.
    input:null
    output:null
    date:20200830
    */
class CompLibTrle : public ADB::CompressionQuery {
 private:
  /* data */
 protected:
 public:
  CompLibTrle(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  ADB::length_t runCompression(void);
  ADB::length_t runDecompression(void);
};

} // namespace ADB_AA
#endif
