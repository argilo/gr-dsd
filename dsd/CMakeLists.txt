project(dsd)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

include(git_revision)
git_describe(GIT_TAG)

find_package(LibSndFile REQUIRED)
find_package(ITPP REQUIRED)

file(GLOB SRCS src/*.c src/*.cpp)
file(GLOB HEADERS include/*.h include/*.hpp)

configure_file("src/git_ver.c.in" "${CMAKE_CURRENT_BINARY_DIR}/git_ver.c" @ONLY)
list(APPEND SRCS "${CMAKE_CURRENT_BINARY_DIR}/git_ver.c")

set(LIBS ${LIBS} ${LIBSNDFILE_LIBRARY} ${ITPP_LIBRARY})

add_library(dsd STATIC ${SRCS} ${HEADERS})
target_link_libraries(dsd mbe ${LIBS})
target_include_directories(dsd
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
    PRIVATE "${LIBSNDFILE_INCLUDE_DIR}"
    PRIVATE "${ITPP_INCLUDE_DIR}"
)
set_property(TARGET dsd PROPERTY POSITION_INDEPENDENT_CODE ON)
