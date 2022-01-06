#ifndef _USER_COMPLIB_TCOMP32_HPP_
#define _USER_COMPLIB_TCOMP32_HPP_
#include <CompressionQuery/CompressionQuery.hpp>
namespace ADB {
/*class:CompLibTcomp32
    description: container of tcomp32 algorithm.
    input:null
    output:null
    date:20200831
    */
class CompLibTcomp32 : public ADB::CompressionQuery {
 private:
  /* data */
 protected:
 public:
  CompLibTcomp32(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  ADB::length_t runCompression(void);
  ADB::length_t runDecompression(void);
};

} // namespace ADB_AA
#endif
