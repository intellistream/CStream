#include <CompLibs/CompLibLz4.hpp>
#include <lz4/lz4.h>
using namespace ADB;

ADB::length_t ADB::CompLibLz4::runCompression(void) {
  ADB::length_t ru;
  ru = LZ4_compress_fast((char *) inputBuf, (char *) outputBuf, inputSize, safetySize, 1);
  return ru;
}

ADB::length_t ADB::CompLibLz4::runDecompression(void) {
  ADB::length_t ru;
  ru = LZ4_decompress_safe((char *) inputBuf, (char *) outputBuf, inputSize, safetySize);
  return ru;
}

CompLibLz4::CompLibLz4(ADB::length_t inS,
                       ADB::length_t outS,
                       ADB::length_t safetySize,
                       ADB::memPtr inP,
                       ADB::memPtr outP)
    : CompressionQuery(inS, outS, safetySize, inP, outP) {

}

void ADB::CompLibLz4::reset(ADB::length_t inS,
                            ADB::length_t outS,
                            ADB::length_t safetySize,
                            ADB::memPtr inP,
                            ADB::memPtr outP) {
  CompressionQuery::reset(inS, outS, safetySize, inP, outP);
}