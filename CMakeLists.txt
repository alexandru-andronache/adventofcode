cmake_minimum_required(VERSION 3.15)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
SET(NAME "advent.of.code")
project(${NAME})
set(CMAKE_CXX_STANDARD 17)
SET(COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/common)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(TESTS.COMMON "tests.common")

include(${COMMON_SOURCES}/cmake/gtest.cmake)
include(${COMMON_SOURCES}/../aoc_common.cmake)
file(GLOB utils_src "${COMMON_SOURCES}/src/*.cpp")
SET(ALL_TESTS_FILES all.tests all.tests.cpp)

add_year(2015)
add_year(2016)
add_year(2017)
add_year(2018)
add_year(2019)
add_year(2020)

add_executable(${ALL_TESTS_FILES}
               ${utils_src})

file(GLOB utils_src "common/src/*.cpp")
file(GLOB tests_src "common/tests/*.cpp")
file(GLOB tests_include "common/tests/*.h")
add_executable(${TESTS.COMMON} ${tests_include} common/test.cpp ${tests_src} ${utils_src})

target_include_directories(all.tests PRIVATE ${COMMON_SOURCES}/include)
target_include_directories(${TESTS.COMMON} PRIVATE ${COMMON_SOURCES}/include)

add_dependencies(all.tests googletest_utilities)
add_dependencies(${TESTS.COMMON} googletest_utilities)

target_compile_definitions(all.tests PRIVATE TESTING=1)
target_compile_definitions(${TESTS.COMMON} PRIVATE)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(CMAKE_DEBUG_POSTFIX d)
endif()

target_link_libraries(all.tests
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a)
target_link_libraries(${TESTS.COMMON}
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a)