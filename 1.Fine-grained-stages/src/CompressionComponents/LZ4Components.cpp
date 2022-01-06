#include <CompressionComponents/LZ4Components.hpp>
using namespace ADB;

// LZ4 args
static inline uint32_t lz4_hash(uint32_t x) { return (x * 2654435761U) >> (32 - LZ4_COMPRESS_HASH_BITS); }
LZ4Args::LZ4Args() {
  const lz4_hash_entry_t HASH_FILL = {.offset =INVALID_OFFSET, .word = 0x0};
  for (number_t i = 0; i < LZ4_COMPRESS_HASH_ENTRIES;) {
    hashTable[i++] = HASH_FILL;

  }
  src_ptr = 0;
  literal_head = 0;
  dst_ptr = 0;
  max_ptr = 0;
  match_distance = 0;
  match_length = 0;
  lit_len = 0;

}
void LZ4Args::reset() {
  const lz4_hash_entry_t HASH_FILL = {.offset =INVALID_OFFSET, .word = 0x0};
  for (number_t i = 0; i < LZ4_COMPRESS_HASH_ENTRIES;) {
    hashTable[i++] = HASH_FILL;

  }
  src_ptr = 0;
  literal_head = 0;
  dst_ptr = 0;
  max_ptr = 0;
  match_distance = 0;
  match_length = 0;
  lit_len = 0;
}
LZ4Args::~LZ4Args() {

}
lz4_hash_entry_t LZ4Args::updateHashTable(uint32_t offset, uint32_t word) {
  uint32_t i0 = lz4_hash(word);
  //printf("%x-%x\r\n",i0,word);
  lz4_hash_entry_t ru = hashTable[i0];

  /* if( hashTable[i0].word==word&&hashTable[i0].offset!=INVALID_OFFSET)
   {
     printf("hash hitting,%d,%d-%d,match %d\r\n",i0,hashTable[i0].offset,offset,word);
   }*/
  hashTable[i0].offset = offset;
  hashTable[i0].word = word;
  return ru;
}
//LZ4 flipread

LZ4FlipReadComponent::LZ4FlipReadComponent(compKey_t key,
                                           number_t preference,
                                           StageParseArgsPtr _inArg,
                                           StageParseArgsPtr _outArg,
                                           MemAddresserPtr _inStream,
                                           MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMREAD;
  myLZ4Arg = (LZ4Args *) _inArg->otherPtr;
  setName("lz4-readFilp");
}
void LZ4FlipReadComponent::exeFunction(void) {  //read 32-bit, but only flip 8 bit
//printf("readpos=%d-%d\r\n",myLZ4Arg->src_ptr,inStream->numberOfBitsAllocated/8);
  ru = inStream->readAlignedValue<uint32_t>(&inStream->data[myLZ4Arg->src_ptr]);
  //printf("ru=%ld,",ru);
  /*myLZ4Arg->src_ptr+=1;
  inStream->readOffset+=8;*/
  //myLZ4Arg->src_ptr +=1;
}
// LZ4 hash

LZ4HashComponent::LZ4HashComponent(compKey_t key,
                                   number_t preference,
                                   StageParseArgsPtr _inArg,
                                   StageParseArgsPtr _outArg,
                                   MemAddresserPtr _inStream,
                                   MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::TABLE;
  myLZ4Arg = (LZ4Args *) _inArg->otherPtr;
  privateArg = make_shared<LZ4Args>();
  setName("lz4-hash table");
}
void LZ4HashComponent::exeFunction(void) {

  ru = privateArg->updateHashTable(myLZ4Arg->src_ptr, myLZ4Arg->tempRead);

}
// LZ4 expand searching
LZ4ExpandSearchingComponent::LZ4ExpandSearchingComponent(compKey_t key,
                                                         number_t preference,
                                                         StageParseArgsPtr _inArg,
                                                         StageParseArgsPtr _outArg,
                                                         MemAddresserPtr _inStream,
                                                         MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMREAD;
  myLZ4Arg = (LZ4Args *) _inArg->otherPtr;
  setName("lz4-expand searching");
}
/*
static uint32_t count_match(uint8_t *buf, uint32_t front_idx, uint32_t back_idx, uint32_t max_idx) {
  uint32_t cnt = 0;
  while (back_idx <= max_idx) {
    if (buf[front_idx] == buf[back_idx]) { cnt += 1; }
    else { break; }
    front_idx += 1;
    back_idx += 1;
  }
  return cnt;
}*/

uint32_t LZ4ExpandSearchingComponent::count_match(uint8_t *buf,
                                                  uint32_t front_idx,
                                                  uint32_t back_idx,
                                                  uint32_t max_idx) {
  uint32_t cnt = 0;
  while (back_idx <= max_idx) {
    if (buf[front_idx] == buf[back_idx]) { cnt += 1; }
    else { break; }
    front_idx += 1;
    back_idx += 1;
  }
  return cnt;
}
void LZ4ExpandSearchingComponent::exeFunction(void) {
  //check the hash table
  distance = myLZ4Arg->src_ptr - myLZ4Arg->tempEntry.offset;

  //printf("distance=%d\r\n",distance);
  if (myLZ4Arg->tempEntry.offset != INVALID_OFFSET && distance<0x10000 && distance>
    3 && myLZ4Arg->tempEntry.word == myLZ4Arg->tempRead) //valid
  {
    length = count_match(inStream->getData(), myLZ4Arg->tempEntry.offset, myLZ4Arg->src_ptr, myLZ4Arg->max_ptr);

  } else {
    length = 0;
  }
  if (length < 4) {
    length = 0;
  }
  // exit(0);
  //printf("match%d-%d",inStream->data[0],inStream->data[101094]);
  // printf("valid match,%d-%d-%d\r\n",myLZ4Arg->tempEntry.offset,myLZ4Arg->src_ptr,myLZ4Arg->max_ptr);

  //printf("distance=%d,length=%d,pos=%d\r\n",distance,length,myLZ4Arg->src_ptr);
  // length=5;

  // printf("length=%d,pos=%d\r\n",length,myLZ4Arg->src_ptr);
}
//write sequence
LZ4WriteSequenceComponent::LZ4WriteSequenceComponent(compKey_t key,
                                                     number_t preference,
                                                     StageParseArgsPtr _inArg,
                                                     StageParseArgsPtr _outArg,
                                                     MemAddresserPtr _inStream,
                                                     MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMWRITE;
  myLZ4Arg = (LZ4Args *) _inArg->otherPtr;
  setName("lz4-write sequence");
  privateArg = make_shared<LZ4Args>();
}
uint32_t LZ4WriteSequenceComponent::copy_sequence(uint8_t *dst_buf,
                                                  uint32_t dst_head,
                                                  uint8_t *src_buf,
                                                  uint32_t srcBegin,
                                                  uint32_t srcEnd,
                                                  uint32_t distance,
                                                  uint32_t match_len) {
  uint32_t lit_len = srcEnd - srcBegin;
  uint32_t dst_ptr = dst_head;
  uint8_t *token = &dst_buf[dst_ptr];
  uint32_t remain_len;
  dst_ptr++;
  //write token
  if (lit_len >= 15) {
    token[0] = (15 << 4);
    remain_len = lit_len - 15;
    while (remain_len >= 255) {
      /* code */
      dst_buf[dst_ptr] = 255;
      dst_ptr += 1;
      remain_len -= 255;
    }
    dst_buf[dst_ptr] = remain_len;
    dst_ptr += 1;
  } else {
    token[0] = (lit_len << 4);
  }
  //literal
  ADB_memcpy(&dst_buf[dst_ptr], src_buf, lit_len);
  dst_ptr += lit_len;
  if (match_len > 0) {
    uint16_t *save = (uint16_t *) &dst_buf[dst_ptr];
    *save = distance;

    dst_ptr += 2;
    //match part
    if (match_len >= 15) {
      token[0] = token[0] | 15;
      match_len -= 15;
      while (match_len > 255) {
        /* code */
        dst_buf[dst_ptr] = 255;
        dst_ptr += 1;
        match_len -= 255;
      }

      dst_buf[dst_ptr] = match_len;
      dst_ptr += 1;

    } else {
      /* code */
      token[0] = token[0] | match_len;
    }

  }
  return dst_ptr - dst_head;
}
void LZ4WriteSequenceComponent::exeFunction(void) {
  //printf("match pair<distance=%d,len=%d,idx=%d>\r\n",inArg->remapValue,inArg->remapLength, privateArg->src_ptr);
  if (inArg->remapLength) {
    privateArg->dst_ptr += copy_sequence(outStream->getData(),
                                         privateArg->dst_ptr,
                                         inStream->getData(),
                                         privateArg->literal_head,
                                         privateArg->src_ptr,
                                         inArg->remapValue,
                                         inArg->remapLength);
  }
}

void LZ4WriteSequenceComponent::writeArgFunction(void) {
  if (privateArg->src_ptr >= (inStream->numberOfBitsAllocated >> 3) - 3) {
    inStream->readOffset += 25;
    privateArg->dst_ptr += copy_sequence(outStream->getData(),
                                         privateArg->dst_ptr,
                                         inStream->getData(),
                                         privateArg->literal_head,
                                         inStream->numberOfBitsAllocated >> 3,
                                         0,
                                         0);
    // printf("to the end%d\r\n",myLZ4Arg->match_length);
    outStream->numberOfBitsUsed = myLZ4Arg->dst_ptr << 3;
    // exit(0);
    return;
  }
  if (inArg->remapLength) {
    privateArg->src_ptr += inArg->remapLength;
    privateArg->literal_head = privateArg->src_ptr;
    inStream->readOffset += inArg->remapLength << 3;
    outStream->numberOfBitsUsed = privateArg->dst_ptr << 3;
    myLZ4Arg->src_ptr = privateArg->src_ptr;
  } else {
    myLZ4Arg->src_ptr += 1;
    inStream->readOffset += 8;
    privateArg->src_ptr += 1;
  }

}
//decomp
#define likely(expr)     __builtin_expect((expr) != 0, 1)
#define unlikely(expr)   __builtin_expect((expr) != 0, 0)

LZ4CopyLitComponent::LZ4CopyLitComponent(compKey_t key,
                                         number_t preference,
                                         StageParseArgsPtr _inArg,
                                         StageParseArgsPtr _outArg,
                                         MemAddresserPtr _inStream,
                                         MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMIO;
  myLZ4Arg = (LZ4Args *) _inArg->otherPtr;
  setName("lz4-copy literal");
}

LZ4CopyMatchComponent::LZ4CopyMatchComponent(compKey_t key,
                                             number_t preference,
                                             StageParseArgsPtr _inArg,
                                             StageParseArgsPtr _outArg,
                                             MemAddresserPtr _inStream,
                                             MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMIO;
  myLZ4Arg = (LZ4Args *) _inArg->otherPtr;
  setName("lz4-copy match");
}
//real copy lit
void LZ4CopyLitComponent::exeFunction() {
  src = &inStream->getData()[myLZ4Arg->src_ptr];
  dest = &outStream->getData()[myLZ4Arg->dst_ptr];
  uint8_t cmd = *src++;

  literalLength = (cmd >> 4) & 15; // 0..15
  matchLength = (cmd & 15); //
  rBytes = 1;
  wBytes = 0;
  if (unlikely(literalLength == 15)) {
    uint8_t s;
    do {

      s = *src++;
      literalLength += s;
      rBytes++;
    } while (unlikely(s == 255));
  }
  ADB_memcpy(dest, src, literalLength);
  rBytes += literalLength;
  wBytes += literalLength;
}
void LZ4CopyLitComponent::writeArgFunction() {
  inStream->readOffset += (rBytes) << 3;
  outStream->numberOfBitsUsed += (wBytes) << 3;
  myLZ4Arg->lit_len = literalLength;
  myLZ4Arg->match_length = matchLength;
  myLZ4Arg->src_ptr += rBytes;
  myLZ4Arg->dst_ptr += wBytes;
}
//copy match
void LZ4CopyMatchComponent::exeFunction() {
  src = &inStream->getData()[myLZ4Arg->src_ptr];
  dest = &outStream->getData()[myLZ4Arg->dst_ptr];
  matchLength = myLZ4Arg->match_length;
  uint64_t matchDistance = *(const uint16_t *) src;
  src += 2;
  rBytes = 2;
  uint8_t *ref = dest - matchDistance;
  // extra bytes for matchLength
  if (unlikely(matchLength == 15)) {
    uint8_t s;
    do {

      // unexpected end of input (1 byte needed)
      s = *src++;
      matchLength += s;
      rBytes++;
    } while (unlikely(s == 255));
  }
  ADB_memcpy(dest, ref, matchLength);
  wBytes = matchLength;
}
void LZ4CopyMatchComponent::writeArgFunction() {
  inStream->readOffset += (rBytes) << 3;
  outStream->numberOfBitsUsed += (wBytes) << 3;
  myLZ4Arg->src_ptr += rBytes;
  myLZ4Arg->dst_ptr += wBytes;
}