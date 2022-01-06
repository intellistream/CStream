#ifndef _USER_COMPLIB_LZ4_HPP_
#define _USER_COMPLIB_LZ4_HPP_
#include <CompressionQuery/CompressionQuery.hpp>
namespace ADB {

/*class:CompLibLz4
    description: container of lz4 algorithm.
    input:null
    output:null
    date:20200831
*/
class CompLibLz4 : public ADB::CompressionQuery {
 private:
  /* data */
 protected:
 public:
  CompLibLz4(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  void reset(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP);
  ADB::length_t runCompression(void);
  ADB::length_t runDecompression(void);
};

} // namespace ADB_AA
#endif
