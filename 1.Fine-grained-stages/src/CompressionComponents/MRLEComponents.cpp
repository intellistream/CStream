#include <CompressionComponents/MRLEComponents.hpp>
using namespace std;
//MRLE Table
#define _putc(__ch, __out) *__out++ = (__ch)
#define _getc(in, in_) (in<in_?(*in++):-1)
#define _rewind(in, _in) in = _in
MRLETableComponent::MRLETableComponent(compKey_t key,
                                       number_t preference,
                                       StageParseArgsPtr _inArg,
                                       StageParseArgsPtr _outArg,
                                       MemAddresserPtr _inStream,
                                       MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMIO;
  myMRLEArg = (MRLEArgs *) _inArg->otherPtr;
  setName("mrle-build ");
}
MRLEReadMemComponent::MRLEReadMemComponent(compKey_t key,
                                           number_t preference,
                                           StageParseArgsPtr _inArg,
                                           StageParseArgsPtr _outArg,
                                           MemAddresserPtr _inStream,
                                           MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMREAD;
  myMRLEArg = (MRLEArgs *) _inArg->otherPtr;
  setName("mrle-read mem");
}

MRLEWriteMemComponent::MRLEWriteMemComponent(compKey_t key,
                                             number_t preference,
                                             StageParseArgsPtr _inArg,
                                             StageParseArgsPtr _outArg,
                                             MemAddresserPtr _inStream,
                                             MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMWRITE;
  myMRLEArg = (MRLEArgs *) _inArg->otherPtr;
  setName("mrle-write mem");
}
//build table
void MRLETableComponent::exeFunction() {
  length_t endPos = inStream->numberOfBitsAllocated >> 3;
  uint8_t *ip = inStream->getData();
  uint8_t *in_ = ip + endPos;
  uint8_t *op = outStream->getData();
  uint64_t run = 0;
  int c, pc = -1;
  while ((c = _getc(ip, in_)) != -1) {
    if (c == pc) myMRLEArg->table[c] += (++run % 255) != 0;
    else --table[c], run = 0;
    pc = c;

  }
  for (int i = 0; i < 32; ++i) {
    int j;
    c = 0;
    for (j = 0; j < 8; ++j) c += (myMRLEArg->table[i * 8 + j] > 0) << j;
    _putc(c, op);
  }
  printf("done table\r\n");

}
void MRLETableComponent::writeArgFunction() {
  //ADB_memcpy(myMRLEArg->table,table,sizeof(table));
  outStream->numberOfBitsUsed += 256;
}
//read mem
void MRLEReadMemComponent::exeFunction() {
  uint8_t c;
  length_t pos = inStream->readOffset >> 3;
  uint8_t *ip = &inStream->getData()[pos];
  length_t end = (inStream->numberOfBitsAllocated >> 3) - pos;
  run = 0;
  c = ip[0];
  while (ip[run] == c && run < end) {
    run++;
  }
  //printf("run=%d\r\n",run);
  symbol = c;

}
void MRLEReadMemComponent::writeArgFunction() {
  inStream->readOffset += (run) << 3;
  //run-=1;
  myMRLEArg->shouldRle = myMRLEArg->table[symbol];

  myMRLEArg->symBol = symbol;
  myMRLEArg->runLength = run;
}
//write mem
void MRLEWriteMemComponent::exeFunction() {
  uint32_t run = myMRLEArg->runLength;
  //length_t pos=outStream->numberOfBitsUsed>>3;
  //uint8_t *op=&outStream->getData()[pos];
  bytesW = 1;
  // outStream->writeAlignedValue<uint8_t>(myMRLEArg->symBol);
  // op[0]=myMRLEArg->symBol;
  if (myMRLEArg->shouldRle) { //printf("run=%d\r\n",run);
    while (run > 255) {
      // outStream->writeAlignedValue<uint8_t>(255);
      /*op[bytesW]=255;*/
      run -= 255;
      bytesW += 1;
    }
    // op[bytesW]=run;
    bytesW += 1;
  }
}
void MRLEWriteMemComponent::writeArgFunction() {
  outStream->numberOfBitsUsed += 1 << 3;
}
//decompression 
MRLEDecomTableComponent::MRLEDecomTableComponent(compKey_t key,
                                                 number_t preference,
                                                 StageParseArgsPtr _inArg,
                                                 StageParseArgsPtr _outArg,
                                                 MemAddresserPtr _inStream,
                                                 MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMREAD;
  myMRLEArg = (MRLEArgs *) _inArg->otherPtr;
  setName("mrle-decomp-build ");
}
MRLEDecomReadMemComponent::MRLEDecomReadMemComponent(compKey_t key,
                                                     number_t preference,
                                                     StageParseArgsPtr _inArg,
                                                     StageParseArgsPtr _outArg,
                                                     MemAddresserPtr _inStream,
                                                     MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMREAD;
  myMRLEArg = (MRLEArgs *) _inArg->otherPtr;
  setName("mrle-decomp-read mem ");
}

MRLEDecomWriteMemComponent::MRLEDecomWriteMemComponent(compKey_t key,
                                                       number_t preference,
                                                       StageParseArgsPtr _inArg,
                                                       StageParseArgsPtr _outArg,
                                                       MemAddresserPtr _inStream,
                                                       MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMWRITE;
  myMRLEArg = (MRLEArgs *) _inArg->otherPtr;
  setName("mrle-decomp-write mem ");
}
//decomp table
void MRLEDecomTableComponent::exeFunction() {
  uint8_t *ip = inStream->getData();
  int i, c;
  for (i = 0; i < 32; ++i) {
    int j;
    c = *ip++;//_getc(ip,in_);
    for (j = 0; j < 8; ++j)
      table[i * 8 + j] = (c >> j) & 1;
  }
}
void MRLEDecomTableComponent::writeArgFunction() {
  ADB_memcpy(myMRLEArg->table, table, sizeof(table));
  inStream->readOffset += 256;
}
//decomp mem
void MRLEDecomReadMemComponent::exeFunction() {
  symbol = inStream->readAlignedValue<uint8_t>();
  run = 0;
  uint8_t tc;

  if (myMRLEArg->table[symbol]) {
    tc = inStream->readAlignedValue<uint8_t>();
    run += tc;
    while (tc == 255) {
      tc = inStream->readAlignedValue<uint8_t>();
      run += tc;
    }

  } else {
    run = 1;
  }

}
void MRLEDecomReadMemComponent::writeArgFunction() {
  myMRLEArg->symBol = symbol;
  myMRLEArg->runLength = run;
}
//write mem
void MRLEDecomWriteMemComponent::exeFunction() {
  uint64_t i = 0;
  run = myMRLEArg->runLength;
  symbol = myMRLEArg->symBol;

  for (i = 0; i < run; i++) {
    outStream->writeAlignedValue<uint8_t>(symbol);
  }
}
void MRLEDecomWriteMemComponent::writeArgFunction() {

}

