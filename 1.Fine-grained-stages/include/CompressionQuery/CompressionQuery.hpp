#ifndef ADB_INCLUDE_COMPRESSIONQUERY_COMPRESSIONQUERY_HPP_
#define ADB_INCLUDE_COMPRESSIONQUERY_COMPRESSIONQUERY_HPP_
#include <CommonData/CommonData.hpp>
namespace ADB {

/*class:CompressionQuery
description: container of compression algorithm, parameter, etc.
input:null
output:null
date:20200827
*/
class CompressionQuery {
 protected:
  /* data */
  length_t inputSize, outputSize, safetySize, expectSize;
  ADB::memPtr inputBuf, outputBuf;
  comp_error_type_t erroCode;

 public:
  CompressionQuery(/* args */);
  CompressionQuery(length_t inS, length_t outS, length_t safetySize, memPtr inP, memPtr outP);
  CompressionQuery(length_t inS,
                   length_t outS,
                   length_t safetySize,
                   length_t expSize,
                   memPtr inP,
                   memPtr outP);
  ~CompressionQuery();
  //the virtual function to envoke a compression
  virtual length_t runCompression(void) = 0;
  //the virtual function to envoke a decompression
  virtual length_t runDecompression(void) = 0;
  comp_error_type_t getError(void);
  void reset(length_t inS, length_t outS, length_t safetySize, memPtr inP, memPtr outP);
  void reset(length_t inS, length_t outS, length_t safetySize, length_t expSize, memPtr inP, memPtr outP);
};

} // namespace ADB

#endif