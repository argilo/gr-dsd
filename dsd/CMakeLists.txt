project(dsd)
cmake_minimum_required(VERSION 2.6)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${dsd_SOURCE_DIR}/cmake/")

include(git_revision)
git_describe(GIT_TAG)

find_package(LibSndFile REQUIRED)

FILE(GLOB SRCS *.c)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/git_ver.c.in" "${CMAKE_CURRENT_BINARY_DIR}/git_ver.c" @ONLY)
list(APPEND SRCS "${CMAKE_CURRENT_BINARY_DIR}/git_ver.c" git_ver.h)

INCLUDE_DIRECTORIES(
    "${PROJECT_SOURCE_DIR}"
    "${LIBSNDFILE_INCLUDE_DIR}"
)

SET(LIBS ${LIBS} ${LIBSNDFILE_LIBRARY})

ADD_LIBRARY(dsd ${SRCS})
TARGET_LINK_LIBRARIES(dsd mbe ${LIBS})
add_definitions(-fPIC)
