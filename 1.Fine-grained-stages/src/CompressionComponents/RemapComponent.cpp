#include <CompressionComponents/RemapComponent.hpp>
using namespace ADB;
RemapComponent::RemapComponent() {

}
RemapComponent::~RemapComponent() {

}
RemapComponent::RemapComponent(compKey_t key,
                               number_t preference,
                               StageParseArgsPtr _inArg,
                               StageParseArgsPtr _outArg,
                               MemAddresserPtr _inStream,
                               MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {
  myType = ADB::ARITH;
}

uint32_t remap_floorP1Lb(uint32_t a) {
  //uint32_t t=a;
  // uint32_t ru=0;
  if (a == 0) {
    return 1;
  }

  /*while (t)
  {  ru++;

     t=t>>1;
  }*/
  return 32 - __builtin_clz(a);
}
void RemapComponent::exeFunction(void) {

  n = remap_floorP1Lb(inArg->remapValue);
  value = (inArg->remapValue << 5) | (n - 1);
  // printf("%x:%d\r\n",inArg->remapValue,n);
}

void RemapComponent::writeArgFunction(void) {
  outArg->remapLength = n + 5;
  outArg->remapValue = value;
}

RemapTdicComponent::RemapTdicComponent() {
 tdic32_initTable(tb,TDIC_COMPRESS_HASH_ENTRIES);
}
RemapTdicComponent::~RemapTdicComponent() {

}
RemapTdicComponent::RemapTdicComponent(compKey_t key,
                               number_t preference,
                               StageParseArgsPtr _inArg,
                               StageParseArgsPtr _outArg,
                               MemAddresserPtr _inStream,
                               MemAddresserPtr _outStream)
    : AbstractComponent(key, preference, _inArg, _outArg, _inStream, _outStream) {
  myType = ADB::TABLE;
   tdic32_initTable(tb,TDIC_COMPRESS_HASH_ENTRIES);
}
void RemapTdicComponent::exeFunction(void) {
  uint32_t num=inArg->remapValue;
   uint32_t i0 = tdic32_hash(num);
   tdic32_hash_entry_t ru = tb[i0];
   if(ru.word==num) //found
   {
       value=(i0<<1)|1;
        n = TDIC_COMPRESS_HASH_BITS+ 1;
   }
   else
   {
       value=(num<<1)|0;
       n=33;
        tb[i0].word=num;
   }
  
  // printf("%x:%d\r\n",inArg->remapValue,n);
}

void RemapTdicComponent::writeArgFunction(void) {
  outArg->remapLength = n ;
  outArg->remapValue = value;
}