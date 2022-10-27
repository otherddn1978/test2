cmake_minimum_required(VERSION 3.0.0)
project(lib1 VERSION 0.1.0)


set (SOURCE_LIB lib1.cpp
                lib2.cpp)

add_library(lib1 SHARED ${SOURCE_LIB})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
