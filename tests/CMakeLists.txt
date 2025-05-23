cmake_minimum_required(VERSION 3.1.0)
project(msgpacker_test)

enable_testing()

set (CMAKE_CXX_STANDARD 14)

include_directories(.)

file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h *.hpp)
add_executable(msgpacker_test ${SRCS} ${HDRS})
target_link_libraries(msgpacker_test msgpacker)

add_test(msgpacker_test msgpacker_test)
