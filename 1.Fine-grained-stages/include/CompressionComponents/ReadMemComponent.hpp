
#ifndef ADB_INCLUDE_COMPRESSIONCOMPONENTS_ReadMemCOMPONENT_HPP_
#define ADB_INCLUDE_COMPRESSIONCOMPONENTS_ReadMemCOMPONENT_HPP_
#include <CommonData/CommonData.hpp>
#include <Utils/MemAddresser.hpp>
#include <string>
#include <CompressionComponents/AbstractComponent.hpp>
using namespace std;
namespace ADB {
class ReadMemComponent : public AbstractComponent {
 private:
  /* data */

 public:
  ReadMemComponent(/* args */);
  ReadMemComponent(compKey_t key,
                   number_t preference,
                   StageParseArgsPtr _inArg,
                   StageParseArgsPtr _outArg,
                   MemAddresserPtr _inStream,
                   MemAddresserPtr _outStream);
  ~ReadMemComponent();
  void exeFunction(void);
  void writeArgFunction(void);
};
typedef std::shared_ptr<ReadMemComponent> ReadMemComponentPtr;

}
#endif