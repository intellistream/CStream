#ifndef _USER_COMPLIB_FSE_HPP_
#define _USER_COMPLIB_FSE_HPP_
#include <CompressionQuery/CompressionQuery.hpp>
namespace ADB {
/*class:CompLibFse
    description: container of fse algorithm.
    input:null
    output:null
    date:20200831
    */
class CompLibFse : public ADB::CompressionQuery {
 private:
  /* data */
 protected:
 public:
  CompLibFse(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  ADB::length_t runCompression(void);
  ADB::length_t runDecompression(void);
};

} // namespace ADB_AA
#endif
