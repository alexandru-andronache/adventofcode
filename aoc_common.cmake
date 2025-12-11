function(pad_number_with_0 original_number total_size number)
    string(LENGTH ${original_number} s)
    MATH(EXPR s "${total_size}-${s}")
    string(REPEAT "0" ${s} pad)
    string(APPEND pad ${original_number})
    set(${number} ${pad} PARENT_SCOPE)
endfunction()

function(get_files_for_year YEAR LIST_OF_SOURCE_FILES)
    foreach (day RANGE 1 25)
        pad_number_with_0(${day} 2 day)
        list(APPEND TMP_LIST_OF_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/day${day}/main.cpp")
        if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/day${day}/test.h")
            list(APPEND TMP_LIST_OF_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/day${day}/test.h")
        endif ()
        if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/day${day}/tests/TestClass.h")
            list(APPEND TMP_LIST_OF_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/day${day}/tests/TestClass.h")
        endif ()
        if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/day${day}/tests/TestClass.cpp")
            list(APPEND TMP_LIST_OF_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}/day${day}/tests/TestClass.cpp")
        endif ()
    endforeach()
    
    set("${LIST_OF_SOURCE_FILES}" "${TMP_LIST_OF_SOURCE_FILES}" PARENT_SCOPE)
endfunction()

function(add_year YEAR)
    get_files_for_year(${YEAR} LIST_OF_SOURCE_FILES)

    add_executable(${YEAR}.all.tests
                   common/test.cpp
                   ${LIST_OF_SOURCE_FILES}
                   ${utils_src})

    target_include_directories(${YEAR}.all.tests PRIVATE ${COMMON_SOURCES}/include)

    add_dependencies(${YEAR}.all.tests googletest_utilities)

    target_compile_definitions(${YEAR}.all.tests PRIVATE TESTING=1)
    target_link_libraries(${YEAR}.all.tests
            general pthread
            general libgtest.a)
endfunction()

function(day_common DAY)
    include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
    set(CMAKE_CXX_STANDARD 23)
    SET(COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../../common)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../bin")

    include(${COMMON_SOURCES}/cmake/gtest.cmake)

    include(FetchContent)
    FetchContent_Declare(
      fmt
      GIT_REPOSITORY https://github.com/fmtlib/fmt
      GIT_TAG        11.1.3)
    FetchContent_MakeAvailable(fmt)

    file(GLOB utils_src "${COMMON_SOURCES}/src/*.cpp")

    file(GLOB cpp_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
    file(GLOB h_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

    file(GLOB cpp_files_test "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
    file(GLOB h_files_test "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h")

    add_executable(main main.cpp ${utils_src})
    add_executable(test main.cpp ${cpp_files} ${h_files} ${utils_src} ${cpp_files_test} ${h_files_test} ${COMMON_SOURCES}/test.cpp)
    add_executable(test.sanitize main.cpp ${cpp_files} ${h_files} ${utils_src} ${cpp_files_test} ${h_files_test} ${COMMON_SOURCES}/test.cpp)

    target_include_directories(main PRIVATE ${COMMON_SOURCES}/include)
    target_include_directories(test PRIVATE ${COMMON_SOURCES}/include)
    target_include_directories(test.sanitize PRIVATE ${COMMON_SOURCES}/include)

    add_dependencies(test googletest_utilities)
    add_dependencies(test.sanitize googletest_utilities)

    target_compile_options(test.sanitize PRIVATE -fsanitize=address -fsanitize=undefined -Wall -Werror -Wextra -Wsign-conversion -Wconversion -Wpedantic -Wshadow)
    target_link_options(test.sanitize PRIVATE -fsanitize=address -fsanitize=undefined -Wall -Werror -Wextra -Wsign-conversion -Wconversion -Wpedantic -Wshadow)

    target_compile_definitions(test PRIVATE TESTING=1)
    target_compile_definitions(test.sanitize PRIVATE TESTING=1)

    target_link_libraries(main
                         fmt::fmt)

    target_link_libraries(test
            general pthread
            general c++
            general libgtest.a
            general libgmock.a
            fmt::fmt
            )

    target_link_libraries(test.sanitize
            general pthread
            general c++
            general libgtest.a
            general libgmock.a
            fmt::fmt
            )
endfunction()

function(day_common_with_z3 DAY)
    include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
    set(CMAKE_CXX_STANDARD 23)
    SET(COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../../common)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../bin")

    include(${COMMON_SOURCES}/cmake/gtest.cmake)

    include(FetchContent)
    FetchContent_Declare(Z3
            GIT_REPOSITORY https://github.com/Z3Prover/z3
            GIT_TAG        z3-4.15.3
    )
    FetchContent_MakeAvailable(Z3)

    if(TARGET libz3)
        target_include_directories(libz3 INTERFACE
                $<BUILD_INTERFACE:${z3_SOURCE_DIR}/src/api/c++>
        )
    endif()

    include(FetchContent)
    FetchContent_Declare(
            fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt
            GIT_TAG        11.1.3)
    FetchContent_MakeAvailable(fmt)

    file(GLOB utils_src "${COMMON_SOURCES}/src/*.cpp")

    file(GLOB cpp_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
    file(GLOB h_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

    file(GLOB cpp_files_test "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
    file(GLOB h_files_test "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h")

    add_executable(main main.cpp ${utils_src})
    add_executable(test main.cpp ${cpp_files} ${h_files} ${utils_src} ${cpp_files_test} ${h_files_test} ${COMMON_SOURCES}/test.cpp)
    add_executable(test.sanitize main.cpp ${cpp_files} ${h_files} ${utils_src} ${cpp_files_test} ${h_files_test} ${COMMON_SOURCES}/test.cpp)

    target_include_directories(main PRIVATE ${COMMON_SOURCES}/include)
    target_include_directories(test PRIVATE ${COMMON_SOURCES}/include)
    target_include_directories(test.sanitize PRIVATE ${COMMON_SOURCES}/include)

    add_dependencies(test googletest_utilities)
    add_dependencies(test.sanitize googletest_utilities)

    target_compile_options(test.sanitize PRIVATE -fsanitize=address -fsanitize=undefined -Wall -Werror -Wextra -Wsign-conversion -Wconversion -Wpedantic -Wshadow)
    target_link_options(test.sanitize PRIVATE -fsanitize=address -fsanitize=undefined -Wall -Werror -Wextra -Wsign-conversion -Wconversion -Wpedantic -Wshadow)

    target_compile_definitions(test PRIVATE TESTING=1)
    target_compile_definitions(test.sanitize PRIVATE TESTING=1)

    target_link_libraries(main
            fmt::fmt
            libz3)

    target_link_libraries(test
            general pthread
            general c++
            general libgtest.a
            general libgmock.a
            fmt::fmt
            libz3
    )

    target_link_libraries(test.sanitize
            general pthread
            general c++
            general libgtest.a
            general libgmock.a
            fmt::fmt
    )
endfunction()