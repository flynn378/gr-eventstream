INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_REEF eventstream)

FIND_PATH(
    REEF_INCLUDE_DIRS
    NAMES eventstream/api.h
    HINTS $ENV{REEF_DIR}/include
        ${PC_REEF_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    REEF_LIBRARIES
    NAMES gnuradio-eventstream
    HINTS $ENV{REEF_DIR}/lib
        ${PC_REEF_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(REEF DEFAULT_MSG REEF_LIBRARIES REEF_INCLUDE_DIRS)
MARK_AS_ADVANCED(REEF_LIBRARIES REEF_INCLUDE_DIRS)

