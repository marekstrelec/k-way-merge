cmake_minimum_required(VERSION 3.5)
project(k-way-merge)

set(CMAKE_CXX_STANDARD 11)

# flags
message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -pthread -O3 -Ofast")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -pthread -g ")


add_executable(merge merge.cpp)
target_link_libraries(merge)
