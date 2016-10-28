project(dsd)
cmake_minimum_required(VERSION 2.6)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

include(git_revision)
git_describe(GIT_TAG)

find_package(LibSndFile REQUIRED)
find_package(ITPP REQUIRED)

FILE(GLOB SRCS src/*.c src/*.cpp)
FILE(GLOB HEADERS include/*.h include/*.hpp)

configure_file("src/git_ver.c.in" "${CMAKE_CURRENT_BINARY_DIR}/git_ver.c" @ONLY)
list(APPEND SRCS "${CMAKE_CURRENT_BINARY_DIR}/git_ver.c")

INCLUDE_DIRECTORIES(
    "${PROJECT_SOURCE_DIR}/include"
    "${LIBSNDFILE_INCLUDE_DIR}"
    "${ITPP_INCLUDE_DIR}"
)

SET(LIBS ${LIBS} ${LIBSNDFILE_LIBRARY} ${ITPP_LIBRARY})

ADD_LIBRARY(dsd ${SRCS} ${HEADERS})
TARGET_LINK_LIBRARIES(dsd mbe ${LIBS})
add_definitions(-fPIC)
