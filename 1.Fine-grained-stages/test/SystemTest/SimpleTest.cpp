// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

#include <gtest/gtest.h>

#include <Utils/Logger.hpp>
#include <Utils/TimeTestBench.hpp>
#include <Utils/FileSp.hpp>
#include <CompLibs/CompLibLz4.hpp>
#include <CompLibs/CompLibZlib.hpp>
#include <CompLibs/CompLibTcomp32.hpp>
#include <CompLibs/CompLibFse.hpp>
#include <CompLibs/CompLibTrle.hpp>
#include <filesystem>

using namespace std;
using namespace ADB;
using namespace FILE_SP;

TEST(SystemTest, SimpleTest
) {
//Setup Logs.
setupLogging("benchmark.log", LOG_DEBUG);

//Run the test here.
ADB_INFO("test sp_bin");
setupLogging("benchmark.log", LOG_DEBUG);
std::string urlStr = "../benchmark/datasets/sp_bin";

std::string ltxt = "loading ";
ltxt +=
urlStr;
ADB_INFO(ltxt);
ADB::length_t szt, compedSize;
memPtr_shared sourceBuf = loadByteFile(FILE_SP::autoUrl(urlStr), &szt);
if (!sourceBuf) {
ADB_ERROR("Can not open file!");
return;
}
ADB_INFO("open file: " +
    FILE_SP::autoUrl(urlStr)
);
/*Note:
The memCeil_t * (unsigned char *)doesn't have a ruction & deruction function, as it is
legacy C pointer representing a continuous memory area.
In this case, the make_shared will only FAIL
*/
memPtr_shared outBuf0 = std::shared_ptr<ADB::memCeil_t>(new ADB::memCeil_t[szt],
                                                        [](ADB::memCeil_t *p) {
                                                          delete[] p;
                                                        });

memPtr_shared outBuf1 = std::shared_ptr<ADB::memCeil_t>(new ADB::memCeil_t[szt * 2],
                                                        [](ADB::memCeil_t *p) {
                                                          delete[] p;
                                                        });
TimeTestBench ttb;

//lz4
CompLibLz4 lz4Lib = CompLibLz4(szt, szt, szt, sourceBuf.get(), outBuf0.get());
compedSize = ttb.runTest(lz4Lib, ADB::COMP);
printf("LZ4 %ld:%ld,%ld us\r\n", szt, compedSize, ttb.lastTime);
//zlib
CompLibZlib zLib = CompLibZlib(szt, szt, szt, sourceBuf.get(), outBuf1.get());
compedSize = ttb.runTest(zLib, ADB::COMP);
printf("zLib %ld:%ld,%ld us\r\n", szt, compedSize, ttb.lastTime);
//tcomp32
CompLibTcomp32 tLib = CompLibTcomp32(szt, szt, szt, sourceBuf.get(), outBuf1.get());
compedSize = ttb.runTest(tLib, ADB::COMP);
if (!compedSize) {
printf("error in tcomp, code %d\r\n", tLib.
getError()
);
} else {
printf("tcomp %ld:%ld,%ld us\r\n", szt, compedSize, ttb.lastTime);
}
//fse
CompLibFse fseLib = CompLibFse(szt, szt, szt, sourceBuf.get(), outBuf1.get());
compedSize = ttb.runTest(fseLib, ADB::COMP);
printf("fse %ld:%ld,%ld us\r\n", szt, compedSize, ttb.lastTime);
//turbo rle
CompLibTrle trleLib = CompLibTrle(szt, szt, szt, sourceBuf.get(), outBuf1.get());
compedSize = ttb.runTest(trleLib, ADB::COMP);
printf("turoboRLE %ld:%ld,%ld us\r\n", szt, compedSize, ttb.lastTime);
return;
}