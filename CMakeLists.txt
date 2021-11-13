cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
Project(OpenXaml VERSION 0.1.0)

option(BUILD_SAMPLE_APPLICATION "Build a sample application" ON)
option(BUILD_DOCUMENTATION "Build the documentation" OFF)
option(ENABLE_LINTER "Run linter" OFF)

#these are currently tested and verified against windows vcpkg, linux probably works
find_package(glfw3 CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(harfbuzz CONFIG REQUIRED)
find_package(XercesC CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

if(WIN32)
	add_compile_options(-W4) #the unused is temporary (hopefully)
else()
	add_compile_options(-Wall -Wextra)
endif()

set (CMAKE_CXX_STANDARD 17)

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

#stollen from https://github.com/ttroy50/cmake-examples/blob/master/04-static-analysis/clang-format/cmake/modules/clang-format.cmake
set(CLANG_FORMAT_EXCLUDE_PATTERNS "build" "vcpkg")
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h *.c)
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    foreach (EXCLUDE_PATTERN ${CLANG_FORMAT_EXCLUDE_PATTERNS})
        string(FIND ${SOURCE_FILE} ${EXCLUDE_PATTERN} PROJECT_TRDPARTY_DIR_FOUND)
        if (NOT ${PROJECT_TRDPARTY_DIR_FOUND} EQUAL -1)
            list(REMOVE_ITEM ALL_SOURCE_FILES ${SOURCE_FILE})
        endif ()
    endforeach()
endforeach ()

add_custom_target(
    format
    COMMAND clang-format
    -style=file
    -i
    ${ALL_SOURCE_FILES}
)

if(${ENABLE_LINTER})
    find_program(TIDY NAMES clang-tidy-9 clang-tidy)
    if(${TIDY} STREQUAL "TIDY-NOTFOUND")
        message(FATAL_ERROR "clang-tidy not found! Necessary for linting!")
    else()
        message(STATUS "Found clang-tidy in ${TIDY}")
    endif()
    
    set(CMAKE_CXX_CLANG_TIDY 
        ${TIDY};
        --checks=readability-*,-readability-magic-numbers,performance-*,portability-*,modernize-*,-modernize-use-trailing-return-type;
        )
    set(CMAKE_C_CLANG_TIDY 
        ${TIDY};
        --checks=readability-*,-readability-magic-numbers,performance-*,portability-*,-clang-analyzer-security.insecureAPI.*;
        )
endif()