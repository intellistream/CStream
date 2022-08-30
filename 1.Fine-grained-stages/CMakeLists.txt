# Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

cmake_minimum_required(VERSION 3.14)
project(aliancedb CXX C)

# Judge the os system

if (UNIX AND NOT APPLE)
    add_definitions(-DUSELOG4CXX)
    MESSAGE(STATUS "Enable Log4CXX")
endif (UNIX AND NOT APPLE)


#gcc options
if (NOT DEFINED ENV{CC})
    set(ENV{CC} "/usr/bin/gcc")
    message(STATUS "auto set GCC= " $ENV{CC})
else ()
    message(STATUS "you have set CC= " $ENV{CC})
endif ()
#g++ options
if (NOT DEFINED ENV{CXX})
    set(ENV{CXX} "/usr/bin/g++")
    message(STATUS "auto set G++= " $ENV{CXX})
else ()
    message(STATUS "you have set CXX= " $ENV{CXX})
endif ()
#configure the specific Meter
if (NOT DEFINED ENV{METER})
    set(ENV{METER} EspMeter)
    message(STATUS "auto set Meter= " $ENV{METER})
else ()
    message(STATUS "you have set Meter= " $ENV{METER})
endif ()
include_directories(${PROJECT_SOURCE_DIR}/include/Utils/Meters/$ENV{METER})
#lib output, change this env if cross compile need
if (NOT DEFINED ENV{LIB_OUT_PATH})
    set(ENV{LIB_OUT_PATH} lib)
    message(STATUS "auto set output path of the lib at " $ENV{LIB_OUT_PATH})
else ()
    message(STATUS "you have set output path of the lib at " $ENV{LIB_OUT_PATH})
endif ()
set(CMAKE_C_COMPILER $ENV{CC})
set(CMAKE_CXX_COMPILER $ENV{CXX})
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/$ENV{CC}_build)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/$ENV{CC}_build)
# Custom CMake find instructions and macros
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
include(cmake/macros.cmake)
include(cmake/default.cmake)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#gcc 10 g++10
#message(STATUS "sudo add-apt-repository 'deb http://mirrors.kernel.org/ubuntu hirsute main universe'")
#message(STATUS "sudo apt-get update")
#message(STATUS "sudo apt install gcc-11 g++-11")
#message(STATUS "sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 11")
#message(STATUS "sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 11")

# Set Optimization Flags
set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -Werror=return-type -Werror=unused-variable -Werror=unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DNO_RACE_CHECK -DADB_DEBUG_MODE=1")
set(CMAKE_CXX_FLAGS_RELEASE "-Wno-ignored-qualifiers -Wno-sign-compare -O3")

# Set LOGGING_LEVEL Flag
if (ADB_LOGGING_LEVEL)
    get_log_level_value(ADB_LOGGING_VALUE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DADB_LOGGING_LEVEL=${ADB_LOGGING_VALUE}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DADB_LOGGING_LEVEL=${ADB_LOGGING_VALUE}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DADB_LOGGING_LEVEL=${ADB_LOGGING_VALUE}")
else (ADB_LOGGING_LEVEL)
    message("---Everything will be logged")
endif (ADB_LOGGING_LEVEL)

message(STATUS "CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE}")


# Log4cc
find_package(Log4cxx REQUIRED)
include_directories(${Log4cxx_INCLUDE_DIR})
set(LIBRARIES ${LIBRARIES} ${Log4cxx_LIBRARY})

if (LOG4CXX_FOUND)
    message(STATUS "LOG4CXX found")
else (LOG4CXX_FOUND)
    message(STATUS "LOG4CXX not found")
    message(STATUS "On Ubuntu, install the package by the following command!")
    message(STATUS "sudo apt-get install -y liblog4cxx-dev")
endif (LOG4CXX_FOUND)
set(Log4cxx_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/contrib) #the cross compiler may fail to find include, so just contain it


if (ENABLE_UNIT_TESTS)
    enable_testing()
    # Google Test
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.11.0
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)
endif ()

# Print all used include directories
message(STATUS "INCLUDE_DIRS:")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach (dir ${dirs})
    message(STATUS "  - ${dir}")
endforeach ()

#other dependencies, temp
set(LIBRARIES ${LIBRARIES})
message(STATUS " Libraries: ${LIBRARIES}")

# Add Source Code
add_subdirectory(src)

# Add Library
get_sources(ADB_SOURCE_FILES)
get_headers(ADB_HEADER_FILES)

add_library(aliancedb SHARED ${ADB_SOURCE_FILES} ${ADB_HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(aliancedb PUBLIC "include")
target_include_directories(aliancedb PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(aliancedb PUBLIC ${LIBRARIES})

#Add benchmarks with command
add_subdirectory(benchmark)

#Add tests (based on GTest suits)
if (ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif ()

install(DIRECTORY "include" DESTINATION "/aliancedb" COMPONENT aliancedb)

