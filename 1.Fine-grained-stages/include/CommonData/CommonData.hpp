//
// Created by tony on 2021/9/28.
//

#ifndef ADB_INCLUDE_COMMONDATA_COMMONDATA_HPP_
#define ADB_INCLUDE_COMMONDATA_COMMONDATA_HPP_
#include <stdint.h>
#include <memory>
#include <Utils/Logger.hpp>
namespace ADB {
typedef int64_t length_t;
typedef uint32_t number_t;

typedef uint8_t *memPtr;
typedef uint8_t memCeil_t;
#define BITS_TO_BYTES(x) (((x)+7)>>3)
#define BYTES_TO_BITS(x) ((x)<<3)
typedef enum {
  COMP = 1,
  DECOM,
  COMPLEN,
  DECOMLEN
} query_type_t;
typedef enum {
  MEMIO,
  MEMREAD,
  MEMWRITE,
  CACULATION,
  TABLE,
  ARITH,
  OTHER
} algo_type_t;
typedef enum {
  NO_ERROR = 0,
  WRONG_INPUT_SIZE,
  WRONG_FORMAT,
  LACK_ALGO_BUF,
  INVALID_RESOURCE
} comp_error_type_t;
class StageParseArgs {
 public:
  StageParseArgs();
  StageParseArgs(length_t _remapLength, uint64_t _remapValue);
  StageParseArgs(length_t _remapLength, uint64_t _remapValue, uint64_t _offset);
  StageParseArgs(length_t _remapLength, uint64_t _remapValue, uint64_t _offset, void *_otherPtr);
  ~StageParseArgs();

  length_t remapLength;
  uint64_t remapValue;
  uint64_t offset;
  void *otherPtr;
};
typedef std::shared_ptr<StageParseArgs> StageParseArgsPtr;
typedef std::shared_ptr<ADB::memCeil_t> memPtr_shared;
//build in functions

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define ADB_memcpy(dst, src, size) __builtin_memcpy(dst, src, size)
#else
#define ADB_memcpy(dst, src, size) memcpy(dst, src, size)
#endif
//machine specific defines
#define MACHINE_L1_BYTES 32*1024
}
#endif
