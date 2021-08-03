function(add_year YEAR USE_SSL)
    file(GLOB_RECURSE ${YEAR}_src_files_h "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/*.h")
    file(GLOB_RECURSE ${YEAR}_src_files_cpp "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/*.cpp")

    list(FILTER ${YEAR}_src_files_cpp EXCLUDE REGEX ".*test.cpp$")
    list(FILTER ${YEAR}_src_files_h EXCLUDE REGEX ".*cmake-build-debug.*")
    list(FILTER ${YEAR}_src_files_cpp EXCLUDE REGEX ".*cmake-build-debug.*")

    list(APPEND ALL_TESTS_FILES ${${YEAR}_src_files_cpp} ${${YEAR}_src_files_h})

    add_executable(${YEAR}.all.tests
                   all.tests.cpp
                   ${${YEAR}_src_files_cpp}
                   ${${YEAR}_src_files_h}
                   ${utils_src})

    target_include_directories(${YEAR}.all.tests PRIVATE ${COMMON_SOURCES}/include)

    add_dependencies(${YEAR}.all.tests googletest_utilities)

    target_compile_definitions(${YEAR}.all.tests PRIVATE TESTING=1 USE_OPENSSL={USE_SSL})
endfunction()