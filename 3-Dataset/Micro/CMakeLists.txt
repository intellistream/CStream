cmake_minimum_required(VERSION 2.8)

#compiler options
if (NOT DEFINED ENV{CC})
    set(ENV{CC} gcc)
    message(STATUS "auto set GCC= " $ENV{CC})
else ()
    message(STATUS "you have set CC= " $ENV{CC})
endif ()
if (NOT DEFINED ENV{CXX})
    set(ENV{CXX} g++)
    message(STATUS "auto set G++= " $ENV{CXX})
else ()
    message(STATUS "you have set G++= " $ENV{CXX})
endif ()
set(CMAKE_CXX_COMPILER $ENV{CXX})

project(mycpupower C CXX)
#LIB OPTIONS
option(MAKE_LIB "make the library" OFF)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/libbin)
#self
aux_source_directory(${PROJECT_SOURCE_DIR}/src/ MYCPUPOWER_BODY_LIST)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB MYCPUPOWER_H_LIST ${PROJECT_SOURCE_DIR}/include/*.h)

aux_source_directory(${PROJECT_SOURCE_DIR}/example/ EXAMPLE_LIST)
#headers
set(HEADERS_SRC ${MYCPUPOWER_H_LIST})
#generate

add_executable(dataSetTool ${EXAMPLE_LIST} ${MYCPUPOWER_BODY_LIST})
target_link_libraries(dataSetTool tonymathlib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/$ENV{CC}_build)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/$ENV{CC}_build)

message(STATUS "output at " ${EXECUTABLE_OUTPUT_PATH})

