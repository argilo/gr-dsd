project(mbe)
cmake_minimum_required(VERSION 3.8)

file(GLOB SRCS *.c)

add_library(mbe STATIC ${SRCS})
target_include_directories(mbe PUBLIC "${PROJECT_SOURCE_DIR}")
set_property(TARGET mbe PROPERTY POSITION_INDEPENDENT_CODE ON)
