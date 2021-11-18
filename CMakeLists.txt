cmake_minimum_required(VERSION 3.0.0)
project(Address-Book VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Address-Book main.cpp entry.cpp address-book.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
