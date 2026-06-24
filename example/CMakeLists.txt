cmake_minimum_required(VERSION 3.14)
project(woodi-example LANGUAGES C)


### main ###

set(EXE "main")
add_executable(${EXE} ./main.c)


### add library

add_subdirectory(../ ${CMAKE_BINARY_DIR}/woodi)
target_link_libraries(${EXE} woodi)
