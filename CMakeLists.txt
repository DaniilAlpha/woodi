cmake_minimum_required(VERSION 3.14)
project(woodi LANGUAGES C)


### lib ###

set(LIB "woodi")
add_library(${LIB} INTERFACE)

target_include_directories(${LIB} INTERFACE ./)
