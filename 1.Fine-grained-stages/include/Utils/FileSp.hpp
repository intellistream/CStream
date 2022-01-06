#ifndef _USER_FILESP_HPP_
#define _USER_FILESP_HPP_
#include <memory>
#include <stdint.h>
#include <CompressionQuery/CompressionQuery.hpp>
#include <filesystem>
#include <CommonData/CommonData.hpp>
using namespace ADB;
using namespace std;

namespace FILE_SP {

typedef ADB::length_t *lengthPtr;
memPtr_shared loadByteFile(std::string fname, lengthPtr sz);
int8_t writeByteFile(std::string fname, ADB::length_t, memPtr_shared data);
string combineUrl(string absolutePath, string relativePath);
string autoUrl(string relativePath);
}
#endif