cmake_minimum_required(VERSION 3.15)
project(http_c)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(common)

add_executable(http_c
        common/mongoose.c
        common/mongoose.h
        main.cpp HttpClient.cpp HttpClient.h)

target_link_libraries(http_c PRIVATE pthread)
