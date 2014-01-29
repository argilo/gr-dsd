project(mbe)
cmake_minimum_required(VERSION 2.6)

FILE(GLOB SRCS *.c)

include_directories("${PROJECT_SOURCE_DIR}")

ADD_LIBRARY(mbe STATIC ${SRCS})
add_definitions(-fPIC)
