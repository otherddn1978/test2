cmake_minimum_required(VERSION 3.0.0)
project(test VERSION 0.1.0)


set (SOURCE_EXE test.cpp)

add_executable(test1 ${SOURCE_EXE})
target_link_libraries(test1 gtest gmock pthread)

add_test (NAME Test123 COMMAND test1)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
