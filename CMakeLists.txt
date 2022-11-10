cmake_minimum_required(VERSION 3.0.0)
project(hello VERSION 0.1.0)

#add 111111111111111111
#add 222222222222222222

include(CTest)
enable_testing()

set (SOURCE_EXE main.cpp)
add_definitions(-DLIB1)
include_directories(lib1)

add_executable(hello ${SOURCE_EXE})
add_subdirectory(lib1)
add_subdirectory(test1)
target_link_libraries(hello lib1)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
