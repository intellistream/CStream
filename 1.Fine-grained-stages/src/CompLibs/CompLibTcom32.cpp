#include <CompLibs/CompLibTcomp32.hpp>
#include <gbindata/tcomp32.h>
using namespace ADB;

ADB::length_t ADB::CompLibTcomp32::runCompression(void) {
  ADB::length_t ru;
  if (inputSize & 0x03) {
    this->erroCode = WRONG_INPUT_SIZE;
    return 0;
  }
  ru = tcomp32_compress(inputBuf, outputBuf, inputSize);
  return ru;
}

ADB::length_t ADB::CompLibTcomp32::runDecompression(void) {
  ADB::length_t ru;
  ru = tcomp32_decompress(inputBuf, outputBuf, inputSize);
  return ru;
}

CompLibTcomp32::CompLibTcomp32(ADB::length_t inS,
                               ADB::length_t outS,
                               ADB::length_t safetySize,
                               ADB::memPtr inP,
                               ADB::memPtr outP)
    : CompressionQuery(inS, outS, safetySize, inP, outP) {

}

void ADB::CompLibTcomp32::reset(ADB::length_t inS,
                                ADB::length_t outS,
                                ADB::length_t safetySize,
                                ADB::memPtr inP,
                                ADB::memPtr outP) {
  CompressionQuery::reset(inS, outS, safetySize, inP, outP);
}