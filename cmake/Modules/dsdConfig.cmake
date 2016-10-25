INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_DSD dsd)

FIND_PATH(
    DSD_INCLUDE_DIRS
    NAMES dsd/api.h
    HINTS $ENV{DSD_DIR}/include
        ${PC_DSD_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    DSD_LIBRARIES
    NAMES gnuradio-dsd
    HINTS $ENV{DSD_DIR}/lib
        ${PC_DSD_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DSD DEFAULT_MSG DSD_LIBRARIES DSD_INCLUDE_DIRS)
MARK_AS_ADVANCED(DSD_LIBRARIES DSD_INCLUDE_DIRS)

