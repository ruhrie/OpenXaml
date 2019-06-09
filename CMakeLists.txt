cmake_minimum_required(VERSION 3.11)

option(BUILD_SAMPLE_APPLICATION "Build a sample application" ON)
option(BUILD_DOCUMENTATION "Build the documentation" OFF)
add_subdirectory("Dependencies")

add_subdirectory("OpenXaml")

if(BUILD_SAMPLE_APPLICATION)
	add_subdirectory("Sample")
endif(BUILD_SAMPLE_APPLICATION)

add_subdirectory("Schema")

if(BUILD_DOCUMENTATION)
	#Generate the documentation if supported
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
		add_custom_target(doc
			COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile        
			VERBATIM)
	endif(DOXYGEN_FOUND)
endif(BUILD_DOCUMENTATION)
