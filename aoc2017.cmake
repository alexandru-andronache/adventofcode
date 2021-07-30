# 2017 files
file(GLOB_RECURSE 2017_src_files_h "${CMAKE_CURRENT_SOURCE_DIR}/2017/*.h")
file(GLOB_RECURSE 2017_src_files_cpp "${CMAKE_CURRENT_SOURCE_DIR}/2017/*.cpp")

list(FILTER 2017_src_files_cpp EXCLUDE REGEX ".*test.cpp$")
list(FILTER 2017_src_files_h EXCLUDE REGEX ".*cmake-build-debug.*")
list(FILTER 2017_src_files_cpp EXCLUDE REGEX ".*cmake-build-debug.*")

add_executable(2017.all.tests
               all.tests.cpp
               ${2017_src_files_cpp}
               ${2017_src_files_h}
               ${utils_src})

target_include_directories(2017.all.tests PRIVATE ${COMMON_SOURCES}/include)

add_dependencies(2017.all.tests googletest_utilities)

target_compile_definitions(2017.all.tests PRIVATE TESTING=1 USE_OPENSSL=1)