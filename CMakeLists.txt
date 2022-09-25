cmake_minimum_required(VERSION 3.15)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
SET(NAME "advent.of.code")
project(${NAME} VERSION 1.0
                DESCRIPTION "Advent of Code"
                LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
SET(COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/common)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(TESTS.COMMON "tests.common")
set(TESTS.ALL.YEARS "tests.all.years")

include(${COMMON_SOURCES}/cmake/gtest.cmake)
include(${COMMON_SOURCES}/../aoc_common.cmake)
file(GLOB utils_src "${COMMON_SOURCES}/src/*.cpp")

add_year(2015)
add_year(2016)
add_year(2017)
add_year(2018)
add_year(2019)
add_year(2020)
add_year(2021)
add_year(2022)

file(GLOB utils_src "${COMMON_SOURCES}/src/*.cpp")
file(GLOB tests_src "${COMMON_SOURCES}/tests/*.cpp")
file(GLOB tests_include "${COMMON_SOURCES}/tests/*.h")

get_files_for_year(2015 LIST_OF_SOURCE_FILES_2015)
get_files_for_year(2016 LIST_OF_SOURCE_FILES_2016)
get_files_for_year(2017 LIST_OF_SOURCE_FILES_2017)
get_files_for_year(2018 LIST_OF_SOURCE_FILES_2018)
get_files_for_year(2019 LIST_OF_SOURCE_FILES_2019)
get_files_for_year(2020 LIST_OF_SOURCE_FILES_2020)
get_files_for_year(2021 LIST_OF_SOURCE_FILES_2021)
get_files_for_year(2022 LIST_OF_SOURCE_FILES_2022)

add_executable(${TESTS.ALL.YEARS} ${COMMON_SOURCES}/test.cpp ${utils_src}
        ${LIST_OF_SOURCE_FILES_2015}
        ${LIST_OF_SOURCE_FILES_2016}
        ${LIST_OF_SOURCE_FILES_2017}
        ${LIST_OF_SOURCE_FILES_2018}
        ${LIST_OF_SOURCE_FILES_2019}
        ${LIST_OF_SOURCE_FILES_2020}
        ${LIST_OF_SOURCE_FILES_2021}
        ${LIST_OF_SOURCE_FILES_2022})
add_executable(${TESTS.COMMON} ${tests_include} ${COMMON_SOURCES}/test.cpp ${tests_src} ${utils_src})

target_include_directories(${TESTS.ALL.YEARS} PRIVATE ${COMMON_SOURCES}/include)
target_include_directories(${TESTS.COMMON} PRIVATE ${COMMON_SOURCES}/include)

add_dependencies(${TESTS.ALL.YEARS} googletest_utilities)
add_dependencies(${TESTS.COMMON} googletest_utilities)

target_compile_definitions(${TESTS.ALL.YEARS} PRIVATE TESTING=1)
target_compile_definitions(${TESTS.COMMON} PRIVATE TESTING=1)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(CMAKE_DEBUG_POSTFIX d)
endif()

target_link_libraries(${TESTS.ALL.YEARS}
        general pthread
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a)
target_link_libraries(${TESTS.COMMON}
        general pthread
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
        general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a)