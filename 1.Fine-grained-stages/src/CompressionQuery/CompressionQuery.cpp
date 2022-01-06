#include <CompressionQuery/CompressionQuery.hpp>

using namespace ADB;
using namespace std;

/*function:CompressionQuery
description: creat default query
input:null
output:null
date:20200827
*/
ADB::CompressionQuery::CompressionQuery(/* args */) {
  this->inputBuf = nullptr;
  this->outputBuf = nullptr;
  this->inputSize = 0;
  this->outputSize = 0;
  this->erroCode = NO_ERROR;
}

/*function:CompressionQuery
description: creat user specific query
input:ADB::length_t inS,ADB::length_t outS,ADB::memPtr inP,ADB::memPtr outP
output:null
date:20200827
NOTE: for the convnenience of calling real functions in C, the buffers are Pointer in fact, so make
sure they are created by shared_ptr and use xxx.get(). (The CompressionQuery it self will only pass pointer) 
 */
ADB::CompressionQuery::CompressionQuery(ADB::length_t inS,
                                        ADB::length_t outS,
                                        ADB::length_t safetySize,
                                        ADB::memPtr inP,
                                        ADB::memPtr outP) {
  this->reset(inS, outS, safetySize, inP, outP);
}

/*function:CompressionQuery
description: creat user specific query
input:ADB::length_t inS,ADB::length_t outS,ADB::memPtr inP,ADB::memPtr outP
output:null
date:20200827
*/
ADB::CompressionQuery::CompressionQuery(ADB::length_t inS,
                                        ADB::length_t outS,
                                        ADB::length_t safetySize,
                                        ADB::length_t expSize,
                                        ADB::memPtr inP,
                                        ADB::memPtr outP) {
  this->reset(inS, outS, safetySize, expSize, inP, outP);
}

ADB::CompressionQuery::~CompressionQuery() {
}

/*function:reset
description: reset user specific query
input:ADB::length_t inS,ADB::length_t outS,ADB::memPtr inP,ADB::memPtr outP
output:null
date:20200827
*/
void ADB::CompressionQuery::reset(ADB::length_t inS,
                                  ADB::length_t outS,
                                  ADB::length_t safeSize,
                                  ADB::memPtr inP,
                                  ADB::memPtr outP) {
  this->inputBuf = inP;
  this->outputBuf = outP;
  this->inputSize = inS;
  this->outputSize = outS;
  this->safetySize = safeSize;
  this->erroCode = NO_ERROR;
}

/*function:reset
description: reset user specific query
input:ADB::length_t inS,ADB::length_t outS,ADB::memPtr inP,ADB::memPtr outP
output:null
date:20200827
*/
void ADB::CompressionQuery::reset(ADB::length_t inS,
                                  ADB::length_t outS,
                                  ADB::length_t safeSize,
                                  ADB::length_t expSize,
                                  ADB::memPtr inP,
                                  ADB::memPtr outP) {
  this->inputBuf = inP;
  this->outputBuf = outP;
  this->inputSize = inS;
  this->outputSize = outS;
  this->safetySize = safeSize;
  this->expectSize = expSize;
  this->erroCode = NO_ERROR;
}

/*function:getError
description: get the error code (if there is an error)
input:null
output:comp_error_type_t
date:20200827
*/
comp_error_type_t ADB::CompressionQuery::getError(void) {
  return this->erroCode;
}
