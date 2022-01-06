//
// Created by tony on 2021/9/28.
//
#include <CommonData/CommonData.hpp>
using namespace ADB;

StageParseArgs::StageParseArgs() {

}

StageParseArgs::~StageParseArgs() {

}

StageParseArgs::StageParseArgs(length_t _remapLength, uint64_t _remapValue) {
  remapLength = _remapLength;
  remapValue = _remapValue;
  offset = 0;
  otherPtr = nullptr;
}

StageParseArgs::StageParseArgs(length_t _remapLength, uint64_t _remapValue, uint64_t _offset) {
  remapLength = _remapLength;
  remapValue = _remapValue;
  offset = _offset;
  otherPtr = nullptr;
}
StageParseArgs::StageParseArgs(length_t _remapLength, uint64_t _remapValue, uint64_t _offset, void *_otherPtr) {
  remapLength = _remapLength;
  remapValue = _remapValue;
  offset = _offset;
  otherPtr = _otherPtr;
}

