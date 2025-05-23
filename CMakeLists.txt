cmake_minimum_required(VERSION 3.5)
project(msgpacker)

set (CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRCS src/*.c)
file(GLOB_RECURSE HDRS src/*.h src/*.hpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS yes)

add_library(msgpacker ${SRCS})
target_include_directories (msgpacker
                            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
                            /opt/homebrew/include)
target_link_libraries(msgpacker)

option(WITH_TESTS "BUILD WITH TESTS" ON)
if(WITH_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(WITH_TESTS)
