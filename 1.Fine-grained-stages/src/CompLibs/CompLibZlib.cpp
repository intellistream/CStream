#include <CompLibs/CompLibZlib.hpp>
#include <zlib.h>
#include <CompressionTasks/AbstractTask.hpp>
using namespace ADB;

ADB::length_t ADB::CompLibZlib::runCompression(void) {
  ADB::length_t ru;
  uLong I = safetySize;
  compress((Bytef *) outputBuf, &I, (Bytef *) inputBuf, inputSize);
  ru = I;
  return ru;
}

ADB::length_t ADB::CompLibZlib::runDecompression(void) {
  ADB::length_t ru;
  uLong P;
  uncompress(outputBuf, &P, inputBuf, inputSize);
  ru = P;
  return ru;
}

CompLibZlib::CompLibZlib(ADB::length_t inS,
                         ADB::length_t outS,
                         ADB::length_t safetySize,
                         ADB::memPtr inP,
                         ADB::memPtr outP)
    : CompressionQuery(inS, outS, safetySize, inP, outP) {

}

void ADB::CompLibZlib::reset(ADB::length_t inS,
                             ADB::length_t outS,
                             ADB::length_t safetySize,
                             ADB::memPtr inP,
                             ADB::memPtr outP) {
  CompressionQuery::reset(inS, outS, safetySize, inP, outP);
}