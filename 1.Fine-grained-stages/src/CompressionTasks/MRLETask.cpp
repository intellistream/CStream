#include <CompressionTasks/MRLETask.hpp>

#include <memory.h>
MRLETask::MRLETask(/* args */) {
}

MRLETask::~MRLETask() {
}
MRLETask::MRLETask(ADB::length_t inS, ADB::length_t outS, ADB::length_t safetySize, ADB::memPtr inP, ADB::memPtr outP)
    : AbstractTask(inS, outS, safetySize, inP, outP) {
  // the forward (compression) components
  MRLEArgsPtr MRLEArg = make_shared<MRLEArgs>();

  myMrleArg = MRLEArg.get();
  StageParseArgsPtr p0 = make_shared<StageParseArgs>(0, 0, 0, MRLEArg.get());
  MRLEReadMemComponentPtr comp_s0_read = make_shared<MRLEReadMemComponent>(1, 1, p0, p0, inStream, outStream);
  addForwardComponent(comp_s0_read);
  MRLEWriteMemComponentPtr comp_s1_write = make_shared<MRLEWriteMemComponent>(2, 1, p0, p0, inStream, outStream);
  addForwardComponent(comp_s1_write);
  //build table
  MRLETableComponentPtr comp_p0_table = make_shared<MRLETableComponent>(3, 1, p0, p0, inStream, outStream);
  forwardPrepare.push_back(comp_p0_table);


  // backward (decompression)

  MRLEDecomReadMemComponentPtr
      decom_s0_read = make_shared<MRLEDecomReadMemComponent>(1, 1, p0, p0, inStream, outStream);
  addBackwardComponent(decom_s0_read);
  MRLEDecomWriteMemComponentPtr
      decom_s1_write = make_shared<MRLEDecomWriteMemComponent>(2, 1, p0, p0, inStream, outStream);
  addForwardComponent(decom_s1_write);
  //build table
  MRLEDecomTableComponentPtr decom_p0_table = make_shared<MRLEDecomTableComponent>(3, 1, p0, p0, inStream, outStream);
  backwardPrepare.push_back(decom_p0_table);

}
void MRLETask::reset(ADB::length_t inS,
                     ADB::length_t outS,
                     ADB::length_t safetySize,
                     ADB::memPtr inP,
                     ADB::memPtr outP) {
  AbstractTask::reset(inS, outS, safetySize, inP, outP);
  if (myMrleArg) {
    myMrleArg->reset();
  }
  // myLz4Arg->max_ptr=inS;
}