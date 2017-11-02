cmake_minimum_required(VERSION 3.5)
project(k-way-merge)

set(CMAKE_CXX_STANDARD 11)

add_executable(merge merge.cpp)
target_link_libraries(merge)
