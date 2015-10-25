# course work Cmake project
cmake_minimum_required(VERSION 2.8)

set(HEADERS headers.h menu.h stack.h)
set(EXEC Source.cpp menu.cpp stack.cpp)
add_library(gmp)
add_library(gpmxx)

add_executable(res_win ${EXEC} ${HEADERS})
 