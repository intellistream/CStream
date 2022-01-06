//
// Created by tony on 2021/9/28.
//

#include <CompressionComponents/AbstractComponent.hpp>
using namespace ADB;
AbstractComponent::AbstractComponent() {

}
AbstractComponent::AbstractComponent(compKey_t key,
                                     number_t preference,
                                     StageParseArgsPtr _inArg,
                                     StageParseArgsPtr _outArg,
                                     MemAddresserPtr _inStream,
                                     MemAddresserPtr _outStream) {
  myKey = key;
  myPreference = preference;
  // profileInfo.runTime = 0;
  inArg = _inArg;
  outArg = _outArg;
  inStream = _inStream;
  outStream = _outStream;
}
AbstractComponent::~AbstractComponent() {

}
void AbstractComponent::setName(string name) {
  nameTag = name;
}
string AbstractComponent::getName(void) {
  return nameTag;
}
void compProfileInfo_t::reset(void) {
  runTime = 0;
  instructions = 0;
  cacheMiss = 0;
  branchMiss = 0;
}