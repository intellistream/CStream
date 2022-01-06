#ifndef _USER_COMPLIB_ZLIB_HPP_
#define _USER_COMPLIB_ZLIB_HPP_
#include <CompressionQuery/CompressionQuery.hpp>
namespace ADB {
/*class:CompLibZlib
    description: container of zlib algorithm.
    input:null
    output:null
    date:20200831
    */
class CompLibZlib : public ADB::CompressionQuery {
 private:
  /* data */
 protected:
 public:
  CompLibZlib(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  ADB::length_t runCompression(void);
  ADB::length_t runDecompression(void);
};

} // namespace ADB_AA
#endif
