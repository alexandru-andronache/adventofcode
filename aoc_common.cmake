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

    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(CMAKE_DEBUG_POSTFIX d)
    endif()

    if (${USE_SSL} STREQUAL "USE_SSL")
        target_compile_definitions(${YEAR}.all.tests PRIVATE TESTING=1 USE_OPENSSL=1)
        target_link_libraries(${YEAR}.all.tests
                general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
                general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a
                general ssl
                general crypto)
    ELSE ()
        target_compile_definitions(${YEAR}.all.tests PRIVATE TESTING=1)
        target_link_libraries(${YEAR}.all.tests
                general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
                general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a)
    endif ()
endfunction()