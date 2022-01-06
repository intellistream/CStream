#ifndef ADB_INCLUDE_COMPRESSIONCOMPONENTS_MRLECOMPONENTS_HPP_
#define ADB_INCLUDE_COMPRESSIONCOMPONENTS_MRLECOMPONENTS_HPP_
#include <CommonData/CommonData.hpp>
#include <Utils/MemAddresser.hpp>
#include <string>
#include <CompressionComponents/AbstractComponent.hpp>
using namespace std;
namespace ADB {
class MRLEArgs {
 public:
  uint64_t table[256];
  uint8_t symBol, runLength, shouldRle;
  MRLEArgs() {
    uint32_t i;
    for (i = 0; i < 256; i++) {
      table[i] = 0;
    }
    symBol = 0;
    runLength = 0;
    shouldRle = 0;
  }
  void reset() {
    uint32_t i;
    for (i = 0; i < 256; i++) {
      table[i] = 0;
    }
    symBol = 0;
    runLength = 0;
    shouldRle = 0;

  }
  ~MRLEArgs() {

  }
};
typedef std::shared_ptr<MRLEArgs> MRLEArgsPtr;
/*deconstruction of mrle comp:
build table(prepare)
read mem and get run length
write mem
*/
class MRLETableComponent : public AbstractComponent {
 private:
  MRLEArgs *myMRLEArg;
  uint64_t table[256];
 public:
  MRLETableComponent() {

  }

  ~MRLETableComponent() {

  }

  MRLETableComponent(compKey_t key,
                     number_t preference,
                     StageParseArgsPtr _inArg,
                     StageParseArgsPtr _outArg,
                     MemAddresserPtr _inStream,
                     MemAddresserPtr _outStream);
  void exeFunction();
  void writeArgFunction(void);

};
typedef std::shared_ptr<MRLETableComponent> MRLETableComponentPtr;
class MRLEReadMemComponent : public AbstractComponent {
 private:
  MRLEArgs *myMRLEArg;
  uint64_t run;
  uint8_t symbol;
 public:
  MRLEReadMemComponent() {

  }

  ~MRLEReadMemComponent() {

  }

  MRLEReadMemComponent(compKey_t key,
                       number_t preference,
                       StageParseArgsPtr _inArg,
                       StageParseArgsPtr _outArg,
                       MemAddresserPtr _inStream,
                       MemAddresserPtr _outStream);
  void exeFunction();
  void writeArgFunction(void);

};
typedef std::shared_ptr<MRLEReadMemComponent> MRLEReadMemComponentPtr;
class MRLEWriteMemComponent : public AbstractComponent {
 private:
  MRLEArgs *myMRLEArg;
  uint64_t run;
  uint8_t symbol;
  uint32_t bytesW;
 public:
  MRLEWriteMemComponent() {

  }

  ~MRLEWriteMemComponent() {

  }

  MRLEWriteMemComponent(compKey_t key,
                        number_t preference,
                        StageParseArgsPtr _inArg,
                        StageParseArgsPtr _outArg,
                        MemAddresserPtr _inStream,
                        MemAddresserPtr _outStream);
  void exeFunction();
  void writeArgFunction(void);

};
typedef std::shared_ptr<MRLEWriteMemComponent> MRLEWriteMemComponentPtr;
/*deconstruction of mrle decomp:
build table(prepare)
read mem and get run length
write mem
*/

class MRLEDecomTableComponent : public AbstractComponent {
 private:
  MRLEArgs *myMRLEArg;
  uint64_t table[256];
 public:
  MRLEDecomTableComponent() {

  }

  ~MRLEDecomTableComponent() {

  }

  MRLEDecomTableComponent(compKey_t key,
                          number_t preference,
                          StageParseArgsPtr _inArg,
                          StageParseArgsPtr _outArg,
                          MemAddresserPtr _inStream,
                          MemAddresserPtr _outStream);
  void exeFunction();
  void writeArgFunction(void);

};
typedef std::shared_ptr<MRLEDecomTableComponent> MRLEDecomTableComponentPtr;
class MRLEDecomReadMemComponent : public AbstractComponent {
 private:
  MRLEArgs *myMRLEArg;
  uint64_t run;
  uint8_t symbol;
 public:
  MRLEDecomReadMemComponent() {

  }

  ~MRLEDecomReadMemComponent() {

  }

  MRLEDecomReadMemComponent(compKey_t key,
                            number_t preference,
                            StageParseArgsPtr _inArg,
                            StageParseArgsPtr _outArg,
                            MemAddresserPtr _inStream,
                            MemAddresserPtr _outStream);
  void exeFunction();
  void writeArgFunction(void);

};
typedef std::shared_ptr<MRLEDecomReadMemComponent> MRLEDecomReadMemComponentPtr;

class MRLEDecomWriteMemComponent : public AbstractComponent {
 private:
  MRLEArgs *myMRLEArg;
  uint64_t run;
  uint8_t symbol;
 public:
  MRLEDecomWriteMemComponent() {

  }

  ~MRLEDecomWriteMemComponent() {

  }

  MRLEDecomWriteMemComponent(compKey_t key,
                             number_t preference,
                             StageParseArgsPtr _inArg,
                             StageParseArgsPtr _outArg,
                             MemAddresserPtr _inStream,
                             MemAddresserPtr _outStream);
  void exeFunction();
  void writeArgFunction(void);

};
typedef std::shared_ptr<MRLEDecomWriteMemComponent> MRLEDecomWriteMemComponentPtr;

}

#endif