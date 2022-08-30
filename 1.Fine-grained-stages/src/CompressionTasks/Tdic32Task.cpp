#include <CompressionTasks/Tdic32Task.hpp>
#include <CompressionComponents/ReadMemComponent.hpp>
#include <CompressionComponents/RemapComponent.hpp>
#include <CompressionComponents/WriteMemComponent.hpp>
#include <memory.h>
Tdic32Task::Tdic32Task(/* args */) {
}

Tdic32Task::~Tdic32Task() {
}
Tdic32Task::Tdic32Task(ADB::length_t inS,
                       ADB::length_t outS,
                       ADB::length_t safetySize,
                       ADB::memPtr inP,
                       ADB::memPtr outP)
    : AbstractTask(inS, outS, safetySize, inP, outP) {
  // the forward (compression) components
  StageParseArgsPtr p0 = make_shared<StageParseArgs>(0xfffffffe, 0);
  StageParseArgsPtr p1 = make_shared<StageParseArgs>(32, 0);
  StageParseArgsPtr p2 = make_shared<StageParseArgs>(0, 0);
  StageParseArgsPtr p3 = make_shared<StageParseArgs>(0, 0);
  ReadMemComponentPtr comp_s0_read = make_shared<ReadMemComponent>(1, 1, p0, p1, inStream, outStream);
  comp_s0_read->setName("tdic32-read");
  addForwardComponent(comp_s0_read);
  RemapTdicComponentPtr comp_s1_remap = make_shared<RemapTdicComponent>(2, 1, p1, p2, inStream, outStream);
  comp_s1_remap->setName("tdic32-remap");
  addForwardComponent(comp_s1_remap);
  WriteMemComponentPtr comp_s2_write = make_shared<WriteMemComponent>(3, 1, p2, p3, inStream, outStream);
  comp_s2_write->setName("tdic32-write");
  addForwardComponent(comp_s2_write);

  //myComponent->push_back(readComp);

}