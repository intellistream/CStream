#include <CompLibs/CompLibTrle.hpp>
#include <gbindata/turboRLE/trle.h>
using namespace ADB;

ADB::length_t ADB::CompLibTrle::runCompression(void) {
  ADB::length_t ru;
  ru = trlec(inputBuf, inputSize, outputBuf);
  return ru;
}

ADB::length_t ADB::CompLibTrle::runDecompression(void) {
  ADB::length_t ru;
  ru = trled(inputBuf, inputSize, outputBuf, safetySize);
  return ru;
}

CompLibTrle::CompLibTrle(ADB::length_t inS,
                         ADB::length_t outS,
                         ADB::length_t safetySize,
                         ADB::memPtr inP,
                         ADB::memPtr outP)
    : CompressionQuery(inS, outS, safetySize, inP, outP) {

}

void ADB::CompLibTrle::reset(ADB::length_t inS,
                             ADB::length_t outS,
                             ADB::length_t safetySize,
                             ADB::memPtr inP,
                             ADB::memPtr outP) {
  CompressionQuery::reset(inS, outS, safetySize, inP, outP);
}