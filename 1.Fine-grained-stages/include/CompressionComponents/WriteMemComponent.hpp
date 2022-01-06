
#ifndef ADB_INCLUDE_COMPRESSIONCOMPONENTS_WriteMemComponent_HPP_
#define ADB_INCLUDE_COMPRESSIONCOMPONENTS_WriteMemComponent_HPP_
#include <CommonData/CommonData.hpp>
#include <Utils/MemAddresser.hpp>
#include <string>
#include <CompressionComponents/AbstractComponent.hpp>
using namespace std;
namespace ADB {
class WriteMemComponent : public AbstractComponent {
 private:

 public:
  WriteMemComponent(/* args */);
  WriteMemComponent(compKey_t key,
                    number_t preference,
                    StageParseArgsPtr _inArg,
                    StageParseArgsPtr _outArg,
                    MemAddresserPtr _inStream,
                    MemAddresserPtr _outStream);
  ~WriteMemComponent();
  void exeFunction(void);
  void writeArgFunction(void) {

  }
};
typedef std::shared_ptr<WriteMemComponent> WriteMemComponentPtr;

}
#endif