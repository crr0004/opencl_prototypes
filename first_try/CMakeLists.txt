cmake_minimum_required( VERSION 2.6.0 )
project( first_try )

set( SAMPLE_NAME main )
set( SOURCE_FILES 
		main.cpp 
)
set( EXTRA_FILES kernel.cl )


# Set CMAKE_BUILD_TYPE (default = Release)
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
set(CMAKE_BUILD_TYPE Debug)
endif()

############################################################################
# Find OpenCL include and libs
find_path( OPENCL_INCLUDE_DIRS 
NAMES OpenCL/cl.h CL/cl.h
HINTS
	ENV OPENCL_PATH
PATH_SUFFIXES
	include
)
mark_as_advanced(OPENCL_INCLUDE_DIRS)

find_library(OPENCL_LIBRARIES
	NAMES OpenCL libOpenCL.so
	PATH_SUFFIXES
	lib/x86_64/
	/opt/amdgpu-pro/lib64/
	HINTS ENV OPENCL_PATH
)

############################################################################
message(STATUS "Using " ${OPENCL_LIBRARIES})
message(STATUS "Using " ${OPENCL_INCLUDE_DIRS})

set( COMPILER_FLAGS "-fpermissive" )
set( LINKER_FLAGS " " )
set( ADDITIONAL_LIBRARIES "" )
set(LIBS ${OPENCL_LIBRARIES} ${ADDITIONAL_LIBRARIES})
message(STATUS "Including " ${OPENCL_INCLUDE_DIRS} " on all targets")
message(STATUS "Using OpenCL library " ${OPENCL_LIBRARIES})
include_directories(SYSTEM ${OPENCL_INCLUDE_DIRS})

file(GLOB INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )

add_executable( ${SAMPLE_NAME} ${SOURCE_FILES} ${INCLUDE_FILES} ${EXTRA_FILES})
add_executable( list_devices list_devices.cpp ${INCLUDE_FILES} ${EXTRA_FILES})
target_link_libraries(${SAMPLE_NAME} ${LIBS})
target_link_libraries(list_devices ${LIBS})

set_target_properties( ${SAMPLE_NAME} PROPERTIES
                        COMPILE_FLAGS ${COMPILER_FLAGS}
                        LINK_FLAGS ${LINKER_FLAGS}
                     )
set_target_properties( list_devices PROPERTIES
                        COMPILE_FLAGS ${COMPILER_FLAGS}
                        LINK_FLAGS ${LINKER_FLAGS}
                     )

# Set output directory to bin
set(EXECUTABLE_OUTPUT_PATH bin)
target_link_libraries( ${SAMPLE_NAME} ${OPENCL_LIBRARIES} ${ADDITIONAL_LIBRARIES} )
target_link_libraries( list_devices ${OPENCL_LIBRARIES} ${ADDITIONAL_LIBRARIES} )

# Set output directory to bin
set(EXECUTABLE_OUTPUT_PATH bin/)

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
