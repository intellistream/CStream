# adding the Google_Tests_run target
add_executable(Google_Tests_run
        SystemTest/SimpleTest.cpp
        )

# linking Google_Tests_run with ADB_lib which will be tested
target_link_libraries(Google_Tests_run gtest_main aliancedb gbindata z lz4 log4cxx)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/datasets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY /usr/local/lib/libgbindata.so DESTINATION ${EXECUTABLE_OUTPUT_PATH})
file(COPY /usr/local/lib/libgbindata.so DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
gtest_discover_tests(Google_Tests_run)