#include <CompLibs/CompLibFse.hpp>
#include <gbindata/huf0_fse/fse.h>
using namespace ADB;

ADB::length_t ADB::CompLibFse::runCompression(void) {
  ADB::length_t ru;
  ru = FSE_compress(outputBuf, safetySize, inputBuf, inputSize);
  return ru;
}

ADB::length_t ADB::CompLibFse::runDecompression(void) {
  ADB::length_t ru;
  ru = FSE_decompress(outputBuf, safetySize, inputBuf, inputSize);
  return ru;
}

CompLibFse::CompLibFse(ADB::length_t inS,
                       ADB::length_t outS,
                       ADB::length_t safetySize,
                       ADB::memPtr inP,
                       ADB::memPtr outP)
    : CompressionQuery(inS, outS, safetySize, inP, outP) {

}

void ADB::CompLibFse::reset(ADB::length_t inS,
                            ADB::length_t outS,
                            ADB::length_t safetySize,
                            ADB::memPtr inP,
                            ADB::memPtr outP) {
  CompressionQuery::reset(inS, outS, safetySize, inP, outP);
}