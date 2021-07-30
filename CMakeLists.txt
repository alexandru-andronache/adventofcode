cmake_minimum_required(VERSION 3.15)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
SET(NAME "run.all.tests")
project(${NAME})
set(CMAKE_CXX_STANDARD 17)
SET(COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/common)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include(${COMMON_SOURCES}/cmake/gtest.cmake)
include(${COMMON_SOURCES}/cmake/openssl.cmake)

file(GLOB utils_src "${COMMON_SOURCES}/src/*.cpp")

include(${COMMON_SOURCES}/../aoc2015.cmake)
include(${COMMON_SOURCES}/../aoc2016.cmake)

# 2019 files
file(GLOB_RECURSE 2019_src_files_h "${CMAKE_CURRENT_SOURCE_DIR}/2019/*.h")
file(GLOB_RECURSE 2019_src_files_cpp "${CMAKE_CURRENT_SOURCE_DIR}/2019/*.cpp")

list(FILTER 2019_src_files_cpp EXCLUDE REGEX ".*test.cpp$")
list(FILTER 2019_src_files_h EXCLUDE REGEX ".*cmake-build-debug.*")
list(FILTER 2019_src_files_cpp EXCLUDE REGEX ".*cmake-build-debug.*")

add_executable(2019.all.tests
               all.tests.cpp
               ${2019_src_files_cpp}
               ${2019_src_files_h}
               ${utils_src})

# 2020 files
file(GLOB_RECURSE 2020_src_files_h "${CMAKE_CURRENT_SOURCE_DIR}/2020/*.h")
file(GLOB_RECURSE 2020_src_files_cpp "${CMAKE_CURRENT_SOURCE_DIR}/2020/*.cpp")

list(FILTER 2020_src_files_cpp EXCLUDE REGEX ".*test.cpp$")
list(FILTER 2020_src_files_h EXCLUDE REGEX ".*cmake-build-debug.*")
list(FILTER 2020_src_files_cpp EXCLUDE REGEX ".*cmake-build-debug.*")

add_executable(2020.all.tests
               all.tests.cpp
               ${2020_src_files_cpp}
               ${2020_src_files_h}
               ${utils_src})

add_executable(all.tests
               all.tests.cpp
               ${2015_src_files_cpp}
               ${2015_src_files_h}
               ${2016_src_files_cpp}
               ${2016_src_files_h}
               ${2019_src_files_cpp}
               ${2019_src_files_h}
               ${2020_src_files_cpp}
               ${2020_src_files_h}
               ${utils_src})

#
file(GLOB utils_src "common/src/*.cpp")
file(GLOB tests_src "common/tests/*.cpp")
file(GLOB tests_include "common/tests/*.h")
add_executable(test_utilities ${tests_include} common/test.cpp ${tests_src} ${utils_src})

target_include_directories(2019.all.tests PRIVATE ${COMMON_SOURCES}/include)
target_include_directories(2020.all.tests PRIVATE ${COMMON_SOURCES}/include)
target_include_directories(all.tests PRIVATE ${COMMON_SOURCES}/include)
target_include_directories(test_utilities PRIVATE ${COMMON_SOURCES}/include)

add_dependencies(2019.all.tests googletest_utilities)
add_dependencies(2020.all.tests googletest_utilities)
add_dependencies(all.tests googletest_utilities)
add_dependencies(test_utilities googletest_utilities)

target_compile_definitions(2019.all.tests PRIVATE TESTING=1)
target_compile_definitions(2020.all.tests PRIVATE TESTING=1)
target_compile_definitions(all.tests PRIVATE TESTING=1 USE_OPENSSL=1)
target_compile_definitions(test_utilities PRIVATE USE_OPENSSL=1)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(CMAKE_DEBUG_POSTFIX d)
endif()

target_link_libraries(2015.all.tests
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a
        general ssl
        general crypto)
target_link_libraries(2016.all.tests
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a
        general ssl
        general crypto)
target_link_libraries(2019.all.tests
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a)
target_link_libraries(2020.all.tests
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a)
target_link_libraries(all.tests
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a
        general ssl
        general crypto)
target_link_libraries(test_utilities
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a
        general ssl
        general crypto)