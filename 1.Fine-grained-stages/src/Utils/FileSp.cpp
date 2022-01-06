#include <Utils/FileSp.hpp>
#include <stdio.h>
#include <stdlib.h>

using namespace FILE_SP;
namespace fs = std::filesystem;
/*function:loadByteFile
description: load file [fname] 
input:string *fname, FILE_SP::lengthPtr sz
output:memPtr_shared return for loaded in memory file, [sz] for the read size
date:20200827
 */
memPtr_shared FILE_SP::loadByteFile(std::string fname, FILE_SP::lengthPtr sz) {

  FILE *fp = fopen((char *) fname.data(), "rb");

  ADB::length_t len;
  if (fp == 0) {
    return NULL;
  }
  fseek(fp, 0, SEEK_END);
  len = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  memPtr_shared readB = std::shared_ptr<ADB::memCeil_t>(new ADB::memCeil_t[len],
                                                        [](ADB::memCeil_t *p) {
                                                          delete[] p;
                                                        });
  fread(readB.get(), len, 1, fp);
  fclose(fp);
  *sz = len;
  return readB;
}

/*function:writeByteFile
description: write file [fname], with [size] bytes of [data]
input:string *fname, ADB::length_t size, memPtr_shared data
output:int8_t, 1 for success
date:20200827
 */
int8_t FILE_SP::writeByteFile(std::string fname, ADB::length_t size, memPtr_shared data) {
  FILE *fp = fopen((char *) fname.data(), "wb");
  if (fp == 0) {
    return 0;
  }
  fwrite(&data.get()[0], size, 1, fp);
  fclose(fp);
  return 1;
}

//skip the space
static std::string trim(std::string s) {
  if (s.empty()) {
    return s;
  }
  s.erase(0, s.find_first_not_of(" "));
  s.erase(s.find_last_not_of(" ") + 1);
  return s;
}

//get the protool name, if in http(s)
static std::string getTrueUrl(std::string url) {
  if (url.empty())
    return NULL;
  url = trim(url);
  if ("http://" == url.substr(0, 7))
    return url.substr(7, url.size());
  else if ("https://" == url.substr(0, 8))
    return url.substr(8, url.size());
  else
    return url;
}

//get the root folder
static std::string getRootUrl(std::string url) {
  if (url.empty())
    return NULL;
  url = getTrueUrl(url);
  std::string::size_type iPos = 0;
  iPos = url.find_first_of('/');
  if (std::string::npos == iPos)
    return url;
  else
    return url.substr(0, iPos);
}

static std::string getNowDict(std::string url) {
  if (url.empty())
    return NULL;
  url = getTrueUrl(url);
  if (url.empty())
    return NULL;
  std::string::size_type iPos = 0;
  iPos = url.find_last_of('/');
  if (std::string::npos == iPos)
    return url;
  else
    return url.substr(0, iPos);
}

/*function:combineUrl
description:combine url, by [absolutePath] and [relativePath]
input:std::string absolutePath,std::string relativePath
output:std::string, for the combined result
date:20200827
 */
std::string FILE_SP::combineUrl(std::string absolutePath, std::string relativePath) {
  if (absolutePath.empty() || relativePath.empty())
    return NULL;
  //test the type of relative path
  relativePath = trim(relativePath);
  if ("http://" == relativePath.substr(0, 7)) //absolute
    return relativePath.substr(7, relativePath.size());
  if ("https://" == relativePath.substr(0, 8)) //absolute
    return relativePath.substr(8, relativePath.size());
  if ("//" == relativePath.substr(0, 2)) //absolute
    return relativePath.substr(2, relativePath.size());
  else if ("/" == relativePath.substr(0, 1)) { //root
    return getRootUrl(absolutePath) + relativePath;
  } else if ("./" == relativePath.substr(0, 2)) { //current
    return getNowDict(absolutePath) + relativePath.substr(1, relativePath.size());
  } else if ("../" == relativePath.substr(0, 3)) { //upper
    while (!relativePath.empty()) {
      if ("../" == relativePath.substr(0, 3)) {
        absolutePath = getNowDict(absolutePath);
        relativePath = relativePath.substr(3, relativePath.size());
      } else {
        return absolutePath + '/' + relativePath;
      }
    }
  } else
    return absolutePath + '/' + relativePath;
  return NULL;
}

/*function:autoUrl
description: the same as combineUrl function, but absolutePath is just that of myself
input:std::string relativePath
output:std::string, for the combined result
date:20200827
 */
std::string FILE_SP::autoUrl(std::string relativePath) {
  if ("/" == relativePath.substr(0, 1)) {
    return relativePath;
  }
  std::string absolutePath = fs::current_path();
  return combineUrl(absolutePath, relativePath);
}