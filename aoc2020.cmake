# 2020 files
file(GLOB_RECURSE 2020_src_files_h "${CMAKE_CURRENT_SOURCE_DIR}/2020/*.h")
file(GLOB_RECURSE 2020_src_files_cpp "${CMAKE_CURRENT_SOURCE_DIR}/2020/*.cpp")

list(FILTER 2020_src_files_cpp EXCLUDE REGEX ".*test.cpp$")
list(FILTER 2020_src_files_h EXCLUDE REGEX ".*cmake-build-debug.*")
list(FILTER 2020_src_files_cpp EXCLUDE REGEX ".*cmake-build-debug.*")

list(APPEND ALL_TESTS_FILES ${2020_src_files_cpp} ${2020_src_files_h})

add_executable(2020.all.tests
               all.tests.cpp
               ${2020_src_files_cpp}
               ${2020_src_files_h}
               ${utils_src})

target_include_directories(2020.all.tests PRIVATE ${COMMON_SOURCES}/include)

add_dependencies(2020.all.tests googletest_utilities)

target_compile_definitions(2020.all.tests PRIVATE TESTING=1)