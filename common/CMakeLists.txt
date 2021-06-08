cmake_minimum_required(VERSION 3.15)
project(aoc_common)
SET(COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR})
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/gtest.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/openssl.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB utils_src "src/*.cpp")
file(GLOB tests_src "tests/*.cpp")
file(GLOB tests_include "tests/*.h")

add_executable(test_utilities ${tests_include} test.cpp ${tests_src} ${utils_src})

target_include_directories(test_utilities PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_dependencies(test_utilities googletest_utilities)

target_compile_definitions(test_utilities PRIVATE USE_OPENSSL=1)

target_link_libraries(test_utilities
        debug ${source_dir}/../googletest_utilities-build/googletest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtestd.a
        debug ${source_dir}/../googletest_utilities-build/googletest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_maind.a
        debug ssl
        debug crypto)