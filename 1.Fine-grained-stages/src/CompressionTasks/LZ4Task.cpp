#include <CompressionTasks/LZ4Task.hpp>

#include <memory.h>
LZ4Task::LZ4Task(/* args */) {
}

LZ4Task::~LZ4Task() {
  //printf("deconstruct lz4task\r\n");
}
LZ4Task::LZ4Task(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP)
    : AbstractTask(inS, outS, safetySize, inP, outP) {
  // the forward (compression) components
  LZ4ArgsPtr lz4Arg = make_shared<LZ4Args>();
  lz4Arg->max_ptr = inS;
  myLz4Arg = lz4Arg.get();
  StageParseArgsPtr p0 = make_shared<StageParseArgs>(0xfffffffe, 0, 0, lz4Arg.get());
  StageParseArgsPtr p1 = make_shared<StageParseArgs>(0xfffffffe, 0, 0, lz4Arg.get());
  StageParseArgsPtr p2 = make_shared<StageParseArgs>(0xfffffffe, 0, 0, lz4Arg.get());
  StageParseArgsPtr p3 = make_shared<StageParseArgs>(0xfffffffe, 0, 0, lz4Arg.get());
  LZ4FlipReadComponentPtr comp_s0_read = make_shared<LZ4FlipReadComponent>(1, 1, p0, p0, inStream, outStream);
  addForwardComponent(comp_s0_read);
  LZ4HashComponentPtr comp_s1_hash = make_shared<LZ4HashComponent>(2, 1, p0, p1, inStream, outStream);
  addForwardComponent(comp_s1_hash);

  LZ4ExpandSearchingComponentPtr
      comp_s2_expand = make_shared<LZ4ExpandSearchingComponent>(3, 1, p1, p2, inStream, outStream);

  //   comp_s2_expand->setPrivateSrc(runSearch.get());
  addForwardComponent(comp_s2_expand);
  LZ4WriteSequenceComponentPtr
      comp_s3_write = make_shared<LZ4WriteSequenceComponent>(4, 1, p2, p3, inStream, outStream);
  addForwardComponent(comp_s3_write);
  //myComponent->push_back(readComp);
  //decompression components
  /*LZ4CopyLitComponentPtr decom_s0_lit = make_shared<LZ4CopyLitComponent>(1, 1, p0, p0, inStream, outStream);
   addBackwardComponent(decom_s0_lit);
   LZ4CopyMatchComponentPtr decom_s1_match = make_shared<LZ4CopyMatchComponent>(2, 1, p0, p0, inStream, outStream);
   addBackwardComponent(decom_s1_match);*/
}
void LZ4Task::reset(ADB::length_t inS,
                    ADB::length_t outS,
                    ADB::length_t safetySize,
                    ADB::memPtr inP,
                    ADB::memPtr outP) {
  AbstractTask::reset(inS, outS, safetySize, inP, outP);
  if (myLz4Arg) {
    myLz4Arg->reset();
  }
  myLz4Arg->max_ptr = inS;
}