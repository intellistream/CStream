
#ifndef ADB_INCLUDE_COMPRESSIONCOMPONENTS_LZ4COMPONENTS_HPP_
#define ADB_INCLUDE_COMPRESSIONCOMPONENTS_LZ4COMPONENTS_HPP_
#include <CommonData/CommonData.hpp>
#include <Utils/MemAddresser.hpp>
#include <string>
#include <CompressionComponents/AbstractComponent.hpp>
using namespace std;
namespace ADB {
#define INVALID_OFFSET 0XFFFFFFFF
typedef struct { uint32_t offset; uint32_t word; } lz4_hash_entry_t;

#define LZ4_COMPRESS_HASH_BITS 11
#define LZ4_COMPRESS_HASH_ENTRIES (1 << LZ4_COMPRESS_HASH_BITS)
#define LZ4_COMPRESS_HASH_MULTIPLY 2654435761U
#define LZ4_COMPRESS_HASH_SHIFT (32 - LZ4_COMPRESS_HASH_BITS)
class LZ4Args {
 private:
  lz4_hash_entry_t hashTable[LZ4_COMPRESS_HASH_ENTRIES];
 public:
  LZ4Args();
  ~LZ4Args();
  void reset();
  lz4_hash_entry_t tempEntry;
  uint32_t tempRead;
  uint32_t src_ptr, literal_head, dst_ptr, lit_len;
  uint32_t max_ptr, match_distance, match_length;
  lz4_hash_entry_t updateHashTable(uint32_t offset, uint32_t word);
};
typedef std::shared_ptr<LZ4Args> LZ4ArgsPtr;
/*deconstruction of lz4 comp:
   flipReadMem
   hashing (tabling)
   expandSearching (memIO)
   writeMem
   */
class LZ4FlipReadComponent : public AbstractComponent {

 private:
  /* data */
  uint32_t ru;
 public:
  LZ4FlipReadComponent(/* args */) {

  }
  LZ4FlipReadComponent(compKey_t key,
                       number_t preference,
                       StageParseArgsPtr _inArg,
                       StageParseArgsPtr _outArg,
                       MemAddresserPtr _inStream,
                       MemAddresserPtr _outStream);
  ~LZ4FlipReadComponent() {

  }
  LZ4Args *myLZ4Arg;
  void exeFunction(void);
  void writeArgFunction(void) {
    //inStream->readOffset+=8;
    myLZ4Arg->tempRead = ru;
    outArg->remapValue = ru;
  }
};
typedef std::shared_ptr<LZ4FlipReadComponent> LZ4FlipReadComponentPtr;

class LZ4HashComponent : public AbstractComponent {

 private:
  /* data */
  lz4_hash_entry_t ru;
  LZ4ArgsPtr privateArg;
 public:
  LZ4HashComponent(/* args */) {

  }
  LZ4HashComponent(compKey_t key,
                   number_t preference,
                   StageParseArgsPtr _inArg,
                   StageParseArgsPtr _outArg,
                   MemAddresserPtr _inStream,
                   MemAddresserPtr _outStream);
  ~LZ4HashComponent() {

  }
  LZ4Args *myLZ4Arg;
  void exeFunction(void);
  void writeArgFunction(void) {
    /* outArg->remapValue =ru.word;
     outArg->offset=ru.offset;
     outArg->remapLength=inArg->remapValue;*/
    myLZ4Arg->tempEntry = ru;
    //myLZ4Arg->t
  }
};
typedef std::shared_ptr<LZ4HashComponent> LZ4HashComponentPtr;
class LZ4ExpandSearchingComponent : public AbstractComponent {

 private:
  /* data */
  uint32_t length, distance;

 public:
  memPtr privateSrc;
  LZ4ExpandSearchingComponent(/* args */) {

  }
  static uint32_t count_match(uint8_t *buf, uint32_t front_idx, uint32_t back_idx, uint32_t max_idx);
  /*uint32_t count_match(uint32_t fi, uint32_t bi, uint32_t max_idx)
  {
     uint32_t cnt = 0;
    uint32_t front_idx=fi;
     uint32_t back_idx=bi;
  while (back_idx < max_idx) {
    if (inStream->data[front_idx] == inStream->data[back_idx]) { cnt += 1; }
    else {return cnt; }

    front_idx += 1;
    back_idx += 1;
  }
  //printf("%d,%d,match%d-%d,%d",fi,bi,inStream->data[fi],inStream->data[bi],max_idx);
  return cnt;
  }*/
  LZ4ExpandSearchingComponent(compKey_t key,
                              number_t preference,
                              StageParseArgsPtr _inArg,
                              StageParseArgsPtr _outArg,
                              MemAddresserPtr _inStream,
                              MemAddresserPtr _outStream);
  ~LZ4ExpandSearchingComponent() {

  }
  LZ4Args *myLZ4Arg;
  void exeFunction(void);
  void setPrivateSrc(memPtr pSrc) {

    privateSrc = pSrc;
    // printf("src0=%d\r\n",privateSrc[0]);

  }
  void writeArgFunction(void) {
    /* myLZ4Arg->match_length = length;
      myLZ4Arg->match_distance = distance;*/
    // inStream->readOffset += 4;
    outArg->remapValue = distance;
    outArg->remapLength = length;
  }
};
typedef std::shared_ptr<LZ4ExpandSearchingComponent> LZ4ExpandSearchingComponentPtr;
class LZ4WriteSequenceComponent : public AbstractComponent {

 private:
  /* data */
  uint32_t length;
  LZ4ArgsPtr privateArg;
 public:
  LZ4WriteSequenceComponent(/* args */) {

  }
  LZ4WriteSequenceComponent(compKey_t key,
                            number_t preference,
                            StageParseArgsPtr _inArg,
                            StageParseArgsPtr _outArg,
                            MemAddresserPtr _inStream,
                            MemAddresserPtr _outStream);
  ~LZ4WriteSequenceComponent() {

  }
  LZ4Args *myLZ4Arg;
  void exeFunction(void);
  void writeArgFunction(void);
  static uint32_t copy_sequence(uint8_t *dst_buf,
                                uint32_t dst_head,
                                uint8_t *src_buf,
                                uint32_t srcBegin,
                                uint32_t srcEnd,
                                uint32_t distance,
                                uint32_t match_len);
};
typedef std::shared_ptr<LZ4WriteSequenceComponent> LZ4WriteSequenceComponentPtr;
//decompression
/*deconstruction of lz4 decomp:
  copy literal
  copy match
   */
//copy literal
class LZ4CopyLitComponent : public AbstractComponent {

 private:
  /* data */
  uint32_t literalLength, matchLength;
  uint8_t *src, *dest;
  uint32_t rBytes, wBytes;
  //uint32_t readBytes;
 public:
  LZ4CopyLitComponent(/* args */) {

  }
  LZ4CopyLitComponent(compKey_t key,
                      number_t preference,
                      StageParseArgsPtr _inArg,
                      StageParseArgsPtr _outArg,
                      MemAddresserPtr _inStream,
                      MemAddresserPtr _outStream);
  ~LZ4CopyLitComponent() {

  }
  LZ4Args *myLZ4Arg;
  void exeFunction(void);
  void writeArgFunction(void);

};
typedef std::shared_ptr<LZ4CopyLitComponent> LZ4CopyLitComponentPtr;
//copy match

class LZ4CopyMatchComponent : public AbstractComponent {

 private:
  /* data */

  uint32_t literalLength, matchLength;
  uint8_t *src, *dest;
  uint32_t rBytes, wBytes;
 public:
  LZ4CopyMatchComponent(/* args */) {

  }
  LZ4CopyMatchComponent(compKey_t key,
                        number_t preference,
                        StageParseArgsPtr _inArg,
                        StageParseArgsPtr _outArg,
                        MemAddresserPtr _inStream,
                        MemAddresserPtr _outStream);
  ~LZ4CopyMatchComponent() {

  }
  LZ4Args *myLZ4Arg;
  void exeFunction(void);
  void writeArgFunction(void);

};

typedef std::shared_ptr<LZ4CopyMatchComponent> LZ4CopyMatchComponentPtr;
}

#endif