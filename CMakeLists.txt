
########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 3.8)
project(gr-eventstream CXX C)
enable_testing()

#install to PyBOMBS target prefix if defined
if(DEFINED ENV{PYBOMBS_PREFIX})
    set(CMAKE_INSTALL_PREFIX $ENV{PYBOMBS_PREFIX})
    message(STATUS "PyBOMBS installed GNU Radio. Setting CMAKE_INSTALL_PREFIX to $ENV{PYBOMBS_PREFIX}")
endif()

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

#make sure our local CMake Modules path comes first
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Set the version information here
set(VERSION_INFO_MAJOR_VERSION 1)
set(VERSION_INFO_API_COMPAT    0)
set(VERSION_INFO_MINOR_VERSION 0)
set(VERSION_INFO_MAINT_VERSION git)

cmake_policy(SET CMP0011 NEW)

########################################################################
# Compiler specific setup
########################################################################
if((CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    AND NOT WIN32)
    #http://gcc.gnu.org/wiki/Visibility
    add_definitions(-fvisibility=hidden)
endif()

IF(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    SET(CMAKE_CXX_STANDARD 11)
ELSEIF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    SET(CMAKE_CXX_STANDARD 11)
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    SET(CMAKE_CXX_STANDARD 11)
ELSE()
    message(WARNING "C++ standard could not be set because compiler is not GNU, Clang or MSVC.")
ENDIF()

IF(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    SET(CMAKE_C_STANDARD 11)
ELSEIF(CMAKE_C_COMPILER_ID MATCHES "Clang")
    SET(CMAKE_C_STANDARD 11)
ELSEIF(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    SET(CMAKE_C_STANDARD 11)
ELSE()
    message(WARNING "C standard could not be set because compiler is not GNU, Clang or MSVC.")
ENDIF()



########################################################################
# Dependencies setup
########################################################################
#find_package(PythonInterp)
#set(GR_REQUIRED_COMPONENTS RUNTIME BLOCKS PMT)
#find_package(Gnuradio)
#if(NOT PYTHONINTERP_FOUND)
#    message(FATAL_ERROR "Python interpreter required by the build system.")
#endif(NOT PYTHONINTERP_FOUND)
#if(NOT GNURADIO_RUNTIME_FOUND)
#    message(FATAL_ERROR "GR core not found")
#endif(NOT GNURADIO_RUNTIME_FOUND)

# locate gnu radio
#include(FindPkgConfig)

#find_package(CppUnit)
#if(NOT CPPUNIT_FOUND)
#    message(FATAL_ERROR "CPPUNIT NOT FOUND!")
#endif(NOT CPPUNIT_FOUND)

#find_package(Log4Cpp)
#if(NOT LOG4CPP_FOUND)
#    message(FATAL_ERROR "LOG4CPP NOT FOUND!")
#endif(NOT LOG4CPP_FOUND)

########################################################################
# Deal with Controlport.
########################################################################
# Enable Control Port code by default.
#option(ENABLE_GR_CTRLPORT "Enable the Control Port stats." ON)

# This doesn't mean the backend for Control Port (ICE or THRIFT) is
# installed or working. It just means that you want to compile in the
# Control Port related methods of this OOT module. If you are running
# your graph and wish to view Control Port data/stats from this module,
# then your GNU Radio build must deal with ensuring your Control Port
# backend is installed/working.
#if (ENABLE_GR_CTRLPORT)
#    add_definitions(-DGR_CTRLPORT)
#endif()
#message(STATUS "GR_CTRLPORT ${ENABLE_GR_CTRLPORT}.")

# locate python
#include(FindPythonLibs)


########################################################################
# Setup the package config file
########################################################################
#set variables found in the pc.in file
#set(prefix ${CMAKE_INSTALL_PREFIX})
#set(exec_prefix "\${prefix}")
#set(libdir "\${exec_prefix}/lib${LIB_SUFFIX}")
#set(includedir "\${prefix}/include")
#set(grcdir "\${prefix}/share/gnuradio/grc/blocks/")
#set(GR_PKG_DATA_DIR "\${prefix}/share/gnuradio/")
#set(GRC_BLOCKS_DIR      ${GR_PKG_DATA_DIR}/grc/blocks)
#set(GR_LIBRARY_DIR lib${LIB_SUFFIX})

########################################################################
# Install directories
########################################################################
find_package(Gnuradio "3.8" REQUIRED)
#find_package( Boost COMPONENTS date_time accumulators program_options filesystem system regex thread unit_test_framework chrono atomic)
find_package (Gnuradio COMPONENTS blocks pmt filter fft)
include(GrVersion)
include(GrPlatform)


if(NOT CMAKE_MODULES_DIR)
  set(CMAKE_MODULES_DIR lib${LIB_SUFFIX}/cmake)
endif(NOT CMAKE_MODULES_DIR)

set(GR_INCLUDE_DIR      include/eventstream)
set(GR_CMAKE_DIR        ${CMAKE_MODULES_DIR}/eventstream)
set(GR_PKG_DATA_DIR     ${GR_DATA_DIR}/${CMAKE_PROJECT_NAME})
set(GR_PKG_DOC_DIR      ${GR_DOC_DIR}/${CMAKE_PROJECT_NAME})
set(GR_PKG_CONF_DIR     ${GR_CONF_DIR}/${CMAKE_PROJECT_NAME}/conf.d)
set(GR_PKG_LIBEXEC_DIR  ${GR_LIBEXEC_DIR}/${CMAKE_PROJECT_NAME})

########################################################################
# On Apple only, set install name and use rpath correctly, if not already set
########################################################################
if(APPLE)
    if(NOT CMAKE_INSTALL_NAME_DIR)
        set(CMAKE_INSTALL_NAME_DIR
            ${CMAKE_INSTALL_PREFIX}/${GR_LIBRARY_DIR} CACHE
            PATH "Library Install Name Destination Directory" FORCE)
    endif(NOT CMAKE_INSTALL_NAME_DIR)
    if(NOT CMAKE_INSTALL_RPATH)
        set(CMAKE_INSTALL_RPATH
            ${CMAKE_INSTALL_PREFIX}/${GR_LIBRARY_DIR} CACHE
            PATH "Library Install RPath" FORCE)
    endif(NOT CMAKE_INSTALL_RPATH)
    if(NOT CMAKE_BUILD_WITH_INSTALL_RPATH)
        set(CMAKE_BUILD_WITH_INSTALL_RPATH ON CACHE
            BOOL "Do Build Using Library Install RPath" FORCE)
    endif(NOT CMAKE_BUILD_WITH_INSTALL_RPATH)
endif(APPLE)

########################################################################
# Setup doxygen option
########################################################################
if(DOXYGEN_FOUND)
	option(ENABLE_DOXYGEN "Build docs using Doxygen" ON)
else(DOXYGEN_FOUND)
	option(ENABLE_DOXYGEN "Build docs using Doxygen" OFF)
endif(DOXYGEN_FOUND)

########################################################################
# Create uninstall target
########################################################################
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
@ONLY)

add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)


########################################################################
# Install all headers in the include directories
########################################################################
#install(
#    DIRECTORY ${CMAKE_SOURCE_DIR}/include/es
#    DESTINATION include COMPONENT "eventstream_devel"
#    FILES_MATCHING
#    PATTERN "*.h"
#    PATTERN "*.hh"
#)

#SET(EVENTSTREAM_INCLUDE_DIRS
#    ${CMAKE_CURRENT_SOURCE_DIR}/include
#    ${CMAKE_CURRENT_SOURCE_DIR}/lib
#)

# uninstall target
#configure_file(
#    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
#    "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
#    IMMEDIATE @ONLY)

#add_custom_target(uninstall
#    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake)

########################################################################
# Add subdirectories
########################################################################
add_subdirectory(include/eventstream)
add_subdirectory(lib)
add_subdirectory(swig)
add_subdirectory(python)
add_subdirectory(grc)
add_subdirectory(apps)


########################################################################
# Install cmake search helper for this library
########################################################################
if(NOT CMAKE_MODULES_DIR)
  set(CMAKE_MODULES_DIR lib${LIB_SUFFIX}/cmake)
endif(NOT CMAKE_MODULES_DIR)

install(FILES cmake/Modules/eventstreamConfig.cmake
    DESTINATION ${CMAKE_MODULES_DIR}/eventstream
)

########################################################################
# Setup the library
########################################################################
#add_subdirectory(lib)
#add_subdirectory(swig)
#add_subdirectory(grc)
#add_subdirectory(python)

#set(GR_PKG_LIBEXEC_DIR ${GR_PYTHON_DIR}/es/)
#set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_INSTALL_PREFIX}/bin/)
#set(GR_RUNTIME_DIR ${CMAKE_INSTALL_PREFIX}/bin/)
#set(GR_PKG_CONF_DIR lib${LIB_SUFFIX}/pkgconfig)

########################################################################
# Print summary
########################################################################
#message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
