#################################################################################
# Copyright ©2013 Advanced Micro Devices, Inc. All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#
# •	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
# •	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or
#  other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#################################################################################


set( SAMPLE_NAME list_devices )
set( SOURCE_FILES 
		list_devices.cpp 
)
set( EXTRA_FILES kernel.cl )

############################################################################

cmake_minimum_required( VERSION 2.6.0 )
project( ${SAMPLE_NAME} )


# Set CMAKE_BUILD_TYPE (default = Release)
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
set(CMAKE_BUILD_TYPE Release)
endif()

############################################################################
# Find OpenCL include and libs
find_path( OPENCL_INCLUDE_DIRS 
NAMES OpenCL/cl.h CL/cl.h
HINTS /opt/AMDAPP/include
)
mark_as_advanced(OPENCL_INCLUDE_DIRS)

find_library(OPENCL_LIBRARIES
	NAMES OpenCL libOpenCL.so.1
)

############################################################################

set( COMPILER_FLAGS "-fpermissive" )
set( LINKER_FLAGS " " )
set( ADDITIONAL_LIBRARIES "" )

file(GLOB INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )

add_executable( ${SAMPLE_NAME} ${SOURCE_FILES} ${INCLUDE_FILES} ${EXTRA_FILES})

set_target_properties( ${SAMPLE_NAME} PROPERTIES
                        COMPILE_FLAGS ${COMPILER_FLAGS}
                        LINK_FLAGS ${LINKER_FLAGS}
                     )
target_link_libraries( ${SAMPLE_NAME} ${OPENCL_LIBRARIES} ${ADDITIONAL_LIBRARIES} )

# Set output directory to bin
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${SAMPLE_NAME})

# Copy extra files to binary directory
foreach( extra_file ${EXTRA_FILES} )
    add_custom_command(
        TARGET ${SAMPLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/${extra_file}  ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/${extra_file}  ./
        )
endforeach( extra_file )