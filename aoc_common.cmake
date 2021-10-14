function(get_files_for_year YEAR LIST_OF_SOURCE_FILES)
    file(GLOB_RECURSE ${YEAR}_src_files_h "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/*.h")
    file(GLOB_RECURSE ${YEAR}_src_files_cpp "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/*.cpp")

    list(FILTER ${YEAR}_src_files_cpp EXCLUDE REGEX ".*test.cpp$")
    list(FILTER ${YEAR}_src_files_h EXCLUDE REGEX ".*cmake-build-debug.*")
    list(FILTER ${YEAR}_src_files_cpp EXCLUDE REGEX ".*cmake-build-debug.*")

    list(APPEND TMP_LIST_OF_SOURCE_FILES ${${YEAR}_src_files_cpp} ${${YEAR}_src_files_h})
    set("${LIST_OF_SOURCE_FILES}" "${TMP_LIST_OF_SOURCE_FILES}" PARENT_SCOPE)
endfunction()

function(add_year YEAR)
    file(GLOB_RECURSE ${YEAR}_src_files_h "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/*.h")
    file(GLOB_RECURSE ${YEAR}_src_files_cpp "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/*.cpp")

    list(FILTER ${YEAR}_src_files_cpp EXCLUDE REGEX ".*test.cpp$")
    list(FILTER ${YEAR}_src_files_h EXCLUDE REGEX ".*cmake-build-debug.*")
    list(FILTER ${YEAR}_src_files_cpp EXCLUDE REGEX ".*cmake-build-debug.*")

    get_files_for_year(${YEAR} LIST_OF_SOURCE_FILES)

    add_executable(${YEAR}.all.tests
                   common/test.cpp
                   ${LIST_OF_SOURCE_FILES}
                   ${utils_src})

    target_include_directories(${YEAR}.all.tests PRIVATE ${COMMON_SOURCES}/include)

    add_dependencies(${YEAR}.all.tests googletest_utilities)

    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(CMAKE_DEBUG_POSTFIX d)
    endif()

    target_compile_definitions(${YEAR}.all.tests PRIVATE TESTING=1)
    target_link_libraries(${YEAR}.all.tests
            general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
            general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a)
endfunction()


function(day_common DAY)
    include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
    set(CMAKE_CXX_STANDARD 17)
    SET(COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../../common)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../bin")

    include(${COMMON_SOURCES}/cmake/gtest.cmake)

    file(GLOB utils_src "${COMMON_SOURCES}/src/*.cpp")

    file(GLOB cpp_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
    file(GLOB h_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

    file(GLOB cpp_files_test "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
    file(GLOB h_files_test "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h")

    add_executable(main main.cpp ${utils_src})
    add_executable(test main.cpp ${cpp_files} ${h_files} ${utils_src} ${cpp_files_test} ${h_files_test} ${COMMON_SOURCES}/test.cpp)

    target_include_directories(main PRIVATE ${COMMON_SOURCES}/include)
    target_include_directories(test PRIVATE ${COMMON_SOURCES}/include)

    add_dependencies(test googletest_utilities)

    target_compile_definitions(test PRIVATE TESTING=1)

    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
            set(CMAKE_DEBUG_POSTFIX d)
    endif()

    target_link_libraries(test
            general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}.a
            general ${source_dir}/../googletest_utilities-build/googletest/${CMAKE_BUILD_TYPE}Libs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}.a)
endfunction()