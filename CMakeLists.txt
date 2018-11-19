cmake_minimum_required(VERSION 3.5)
project("OpenXaml")

set (CMAKE_CXX_STANDARD 11)

find_package( OpenGL REQUIRED )

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BIN_ROOT_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory("Dependencies")

add_subdirectory("OpenXaml")

add_subdirectory("Sample")

add_subdirectory("Schema")

#Generate the documentation if supported
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile        
        VERBATIM)
endif(DOXYGEN_FOUND)
