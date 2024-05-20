cmake_minimum_required(VERSION 3.5)

project(object_wrapper_example VERSION 1.0.0 LANGUAGES C)

set(MAIN "main")

set(SRC_DIR "./")
set(INCLUDE_DIR "../")

file(GLOB SRCS ${SRC_DIR}/*.c)

add_executable(${MAIN} ${SRCS})
target_include_directories(${MAIN} PRIVATE ${INCLUDE_DIR})
