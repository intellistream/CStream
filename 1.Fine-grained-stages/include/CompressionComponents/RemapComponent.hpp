
#ifndef ADB_INCLUDE_COMPRESSIONCOMPONENTS_REMAPCOMPONENT_HPP_
#define ADB_INCLUDE_COMPRESSIONCOMPONENTS_REMAPCOMPONENTT_HPP_
#include <CommonData/CommonData.hpp>
#include <Utils/MemAddresser.hpp>
#include <string>
#include <CompressionComponents/AbstractComponent.hpp>
using namespace std;
namespace ADB {

class RemapComponent : public AbstractComponent {
 private:
  /* data */
  uint64_t value, n;
 public:
  RemapComponent(/* args */);
  RemapComponent(compKey_t key,
                 number_t preference,
                 StageParseArgsPtr _inArg,
                 StageParseArgsPtr _outArg,
                 MemAddresserPtr _inStream,
                 MemAddresserPtr _outStream);
  ~RemapComponent();
  void exeFunction(void);
  void writeArgFunction(void);

};

typedef std::shared_ptr<RemapComponent> RemapComponentPtr;
#define INVALID_OFFSET 0XFFFFFFFF
typedef struct { /*uint32_t idex; */uint32_t word; } tdic32_hash_entry_t;

#define TDIC_COMPRESS_HASH_BITS 11
#define TDIC_COMPRESS_HASH_ENTRIES (1 << TDIC_COMPRESS_HASH_BITS)
#define TDIC_COMPRESS_HASH_MULTIPLY 2654435761U
#define TDIC_COMPRESS_HASH_SHIFT (32 - TDIC_COMPRESS_HASH_BITS)
static inline uint32_t tdic32_hash(uint32_t x) { return (x * 2654435761U) >> (32 - TDIC_COMPRESS_HASH_BITS); }
static inline void tdic32_initTable(tdic32_hash_entry_t *tb, uint32_t tLen) {
  uint32_t i;
  for (i = 0; i < tLen; i++) {
    tb[i].word = INVALID_OFFSET;
  }
  tb[tdic32_hash(INVALID_OFFSET)].word = 0;
}
class RemapTdicComponent : public AbstractComponent {
 private:
  /* data */
  uint64_t value, n;
  tdic32_hash_entry_t tb[TDIC_COMPRESS_HASH_ENTRIES];
 public:
  RemapTdicComponent(/* args */);
  RemapTdicComponent(compKey_t key,
                     number_t preference,
                     StageParseArgsPtr _inArg,
                     StageParseArgsPtr _outArg,
                     MemAddresserPtr _inStream,
                     MemAddresserPtr _outStream);
  ~RemapTdicComponent();
  void exeFunction(void);
  void writeArgFunction(void);

};

typedef std::shared_ptr<RemapTdicComponent> RemapTdicComponentPtr;
}
#endif