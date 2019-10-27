#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT eventstream_sources)
	MESSAGE(STATUS "No C++ sources... skipping swig/")
	return()
endif(NOT eventstream_sources)

########################################################################
# Include swig generation macros
########################################################################
find_package(SWIG)
#find_package(Boost)
find_package(PythonLibs)
if(NOT SWIG_FOUND OR NOT PYTHONLIBS_FOUND)
    return()
endif()
include(GrSwig)
include(GrPython)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
#target_link_libraries(${Boost_LIBRARIES})
########################################################################
# Setup swig generation
########################################################################
set(GR_SWIG_INCLUDE_DIRS ${Boost_INCLUDE_DIR} $<TARGET_PROPERTY:gnuradio::runtime_swig,INTERFACE_INCLUDE_DIRECTORIES>)
set(GR_SWIG_TARGET_DEPS   gnuradio::runtime_swig )

set(GR_SWIG_LIBRARIES gnuradio-eventstream ${Boost_LIBRARIES})
#set(GR_SWIG_DOC_FILE ${CMAKE_CURRENT_BINARY_DIR}/eventstream_swig_doc.i)
#set(GR_SWIG_DOC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include)

GR_SWIG_MAKE(eventstream_swig eventstream_swig.i)

########################################################################
# Install the build swig module
########################################################################
GR_SWIG_INSTALL(TARGETS eventstream_swig DESTINATION ${GR_PYTHON_DIR}/eventstream)

########################################################################
# Install swig .i files for development
########################################################################
install(
    FILES
    eventstream_swig.i
    DESTINATION ${GR_INCLUDE_DIR}/eventstream/swig
)
