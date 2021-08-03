# 2018 files
file(GLOB_RECURSE 2018_src_files_h "${CMAKE_CURRENT_SOURCE_DIR}/2018/*.h")
file(GLOB_RECURSE 2018_src_files_cpp "${CMAKE_CURRENT_SOURCE_DIR}/2018/*.cpp")

list(FILTER 2018_src_files_cpp EXCLUDE REGEX ".*test.cpp$")
list(FILTER 2018_src_files_h EXCLUDE REGEX ".*cmake-build-debug.*")
list(FILTER 2018_src_files_cpp EXCLUDE REGEX ".*cmake-build-debug.*")

list(APPEND ALL_TESTS_FILES ${2018_src_files_cpp} ${2018_src_files_h})

add_executable(2018.all.tests
               all.tests.cpp
               ${2018_src_files_cpp}
               ${2018_src_files_h}
               ${utils_src})

target_include_directories(2018.all.tests PRIVATE ${COMMON_SOURCES}/include)

add_dependencies(2018.all.tests googletest_utilities)

target_compile_definitions(2018.all.tests PRIVATE TESTING=1)