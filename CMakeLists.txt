cmake_minimum_required(VERSION 3.11)
Project(OpenXaml )
option(BUILD_SAMPLE_APPLICATION "Build a sample application" ON)
option(BUILD_DOCUMENTATION "Build the documentation" OFF)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory("Dependencies")

add_subdirectory("OpenXaml")

add_subdirectory("xut")

include(cmake/OpenXaml.cmake)

if(BUILD_SAMPLE_APPLICATION)
	add_subdirectory("Sample")
endif(BUILD_SAMPLE_APPLICATION)

if(BUILD_DOCUMENTATION)
	#Generate the documentation if supported
	find_package(Doxygen REQUIRED)
	if(DOXYGEN_FOUND)
		if(CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
		add_custom_target(doc ALL
			COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile   
			COMMENT "Generating API documentation with Doxygen"     
			VERBATIM)
		endif()
	endif(DOXYGEN_FOUND)
endif(BUILD_DOCUMENTATION)
