#include <CompressionComponents/ReadMemComponent.hpp>
using namespace ADB;
ReadMemComponent::ReadMemComponent() {

}
ReadMemComponent::~ReadMemComponent() {

}
ReadMemComponent::ReadMemComponent(compKey_t key,
                                   number_t preference,
                                   StageParseArgsPtr _inArg,
                                   StageParseArgsPtr _outArg,
                                   MemAddresserPtr _inStream,
                                   MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMREAD;
}
void ReadMemComponent::exeFunction(void) {

  switch (inArg->remapLength) {
    case 0xffffffffc:outArg->remapValue = inStream->readAlignedValue<uint8_t>();
      break;
    case 0xfffffffd:outArg->remapValue = inStream->readAlignedValue<uint16_t>();
      break;
    case 0xfffffffe:outArg->remapValue = inStream->readAlignedValue<uint32_t>();
      break;
    case 0xfffffff:outArg->remapValue = inStream->readAlignedValue<uint64_t>();
      break;
    default:outArg->remapValue = inStream->readValue<uint64_t>(inArg->remapValue + inArg->offset);
      break;
  }
}

void ReadMemComponent::writeArgFunction(void) {

}

