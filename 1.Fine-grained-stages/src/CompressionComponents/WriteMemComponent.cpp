#include <CompressionComponents/WriteMemComponent.hpp>
using namespace ADB;
WriteMemComponent::WriteMemComponent() {

}
WriteMemComponent::~WriteMemComponent() {

}
WriteMemComponent::WriteMemComponent(compKey_t key,
                                     number_t preference,
                                     StageParseArgsPtr _inArg,
                                     StageParseArgsPtr _outArg,
                                     MemAddresserPtr _inStream,
                                     MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {

  myType = ADB::MEMWRITE;
}
void WriteMemComponent::exeFunction(void) {
  outStream->writeValue<uint64_t>(inArg->remapValue, inArg->remapLength);
  //printf("write %d bits\r\n",inArg->remapLength);
}

