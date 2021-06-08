set(BUILD_OPENSSL ON)
set(OPENSSL_BUILD_VERSION 1.1.0h)

add_subdirectory(${COMMON_SOURCES}/external/openssl-cmake cmake-openssl)