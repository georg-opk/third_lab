cmake_minimum_required(VERSION 3.26)
project(untitled1)

set(CMAKE_C_STANDARD 99)

add_library(mycalc STATIC mycalc.c)
target_include_directories(mycalc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(untitled1 main.c)
target_link_libraries(untitled1 mycalc)