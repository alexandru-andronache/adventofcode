SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)

ExternalProject_Add(
        googletest_utilities
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.17.0
        TIMEOUT 10
        SOURCE_DIR ${CMAKE_BINARY_DIR}/third_party/googletest/googletest
        CMAKE_ARGS
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
            -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
        -Dgtest_force_shared_crt=ON
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON)

include_directories(${CMAKE_BINARY_DIR}/third_party/googletest/googletest/googletest/include)
include_directories(${CMAKE_BINARY_DIR}/third_party/googletest/googletest/googlemock/include)

link_directories(${CMAKE_BINARY_DIR}/third_party/src/googletest_utilities-build/lib)