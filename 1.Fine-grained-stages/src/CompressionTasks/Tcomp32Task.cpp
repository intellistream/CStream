#include <CompressionTasks/Tcomp32Task.hpp>
#include <CompressionComponents/ReadMemComponent.hpp>
#include <CompressionComponents/RemapComponent.hpp>
#include <CompressionComponents/WriteMemComponent.hpp>
#include <memory.h>
Tcomp32Task::Tcomp32Task(/* args */) {
}

Tcomp32Task::~Tcomp32Task() {
}
Tcomp32Task::Tcomp32Task(ADB::length_t inS,
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
  comp_s0_read->setName("tcomp32-read");
  addForwardComponent(comp_s0_read);
  RemapComponentPtr comp_s1_remap = make_shared<RemapComponent>(2, 1, p1, p2, inStream, outStream);
  comp_s1_remap->setName("tcomp32-remap");
  addForwardComponent(comp_s1_remap);
  WriteMemComponentPtr comp_s2_write = make_shared<WriteMemComponent>(3, 1, p2, p3, inStream, outStream);
  comp_s2_write->setName("tcomp32-write");
  addForwardComponent(comp_s2_write);
  // the backward (decompression) components
  StageParseArgsPtr bp0 = make_shared<StageParseArgs>(0, 5);
  StageParseArgsPtr bp1 = make_shared<StageParseArgs>(0, 0, 1);
  StageParseArgsPtr bp2 = make_shared<StageParseArgs>(32, 32, 32);
  StageParseArgsPtr bp3 = make_shared<StageParseArgs>(0, 0);
  ReadMemComponentPtr decom_s0_read5 = make_shared<ReadMemComponent>(1, 1, bp0, bp1, inStream, outStream);
  decom_s0_read5->setName("tcomp32-read5");
  addBackwardComponent(decom_s0_read5);
  ReadMemComponentPtr decom_s1_readn = make_shared<ReadMemComponent>(2, 1, bp1, bp2, inStream, outStream);
  decom_s1_readn->setName("tcomp32-readn");
  addBackwardComponent(decom_s1_readn);
  WriteMemComponentPtr decom_s2_writeBack = make_shared<WriteMemComponent>(3, 1, bp2, bp3, inStream, outStream);
  decom_s2_writeBack->setName("tcomp32-writeBack");
  addBackwardComponent(decom_s2_writeBack);
  //myComponent->push_back(readComp);

}