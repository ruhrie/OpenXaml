cmake_minimum_required(VERSION 3.14)
Project(OpenXaml VERSION 0.1.0)

option(BUILD_SAMPLE_APPLICATION "Build a sample application" ON)
option(BUILD_DOCUMENTATION "Build the documentation" OFF)

set (CMAKE_CXX_STANDARD 17)

#these are currently tested and verified against windows vcpkg, linux probably works
find_package(glfw3 CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(harfbuzz CONFIG REQUIRED)
find_package(XercesC CONFIG REQUIRED)
find_package(unofficial-angle CONFIG REQUIRED)

add_subdirectory("Dependencies" EXCLUDE_FROM_ALL)

add_subdirectory("OpenXaml")

add_subdirectory("xut")

install(EXPORT OpenXaml DESTINATION "lib")

include(cmake/OpenXaml.cmake)

if(BUILD_SAMPLE_APPLICATION)
	add_subdirectory("Sample")
endif(BUILD_SAMPLE_APPLICATION)

if(BUILD_DOCUMENTATION)
	#Generate the documentation
	find_package(Doxygen REQUIRED)
	if(DOXYGEN_FOUND)
		set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
		add_custom_target(doc ALL
			COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile   
			COMMENT "Generating API documentation with Doxygen"     
			VERBATIM)
	endif(DOXYGEN_FOUND)
endif(BUILD_DOCUMENTATION)
