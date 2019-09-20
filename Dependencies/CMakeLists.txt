include(FetchContent)


FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
)
find_package(glfw3 QUIET)
if(glfw3_FOUND)
	message(STATUS "GLFW found")
else()
	if(DOWNLOAD_MISSING_DEPENDENCIES)
		message(STATUS "GLFW not found, downloading sources")
		FetchContent_GetProperties(glfw)
		if(NOT glfw_POPULATED)
			FetchContent_Populate(glfw)  
		endif()
		set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
		set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
		set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
		set(GLFW_INC ${glfw_SOURCE_DIR}/include ${glfw_BINARY_DIR}/include PARENT_SCOPE)
		add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
	else()
		message(FATAL_ERROR "GLFW not found and downloading sources is disabled")
	endif()
endif()

find_package(xercesc QUIET)
if(xercesc_FOUND)
	message(STATUS "Xerces found")
else()
	if(DOWNLOAD_MISSING_DEPENDENCIES)
		message(STATUS "Xerces not found, downloading sources")
		FetchContent_Declare(xerces
			URL https://www-eu.apache.org/dist//xerces/c/3/sources/xerces-c-3.2.2.tar.gz
			URL_HASH SHA256=dd6191f8aa256d3b4686b64b0544eea2b450d98b4254996ffdfe630e0c610413
		)
		FetchContent_GetProperties(xerces)
		if(NOT xerces_POPULATED)
			FetchContent_Populate(xerces)
		endif()
		set(XERCES_INC ${xerces_SOURCE_DIR}/src ${xerces_BINARY_DIR}/src PARENT_SCOPE)
		add_subdirectory(${xerces_SOURCE_DIR} ${xerces_BINARY_DIR})
	else()
		message(FATAL_ERROR "Xerces not found and downloading sources is disabled")
	endif()
endif()


find_package(freetype QUIET)
if(freetype_FOUND)
	message(STATUS "Freetype found")
else()
	if(DOWNLOAD_MISSING_DEPENDENCIES)
		message(STATUS "Freetype not found, downloading sources")
		FetchContent_Declare(Freetype
			URL https://download.savannah.gnu.org/releases/freetype/freetype-2.10.0.tar.gz
		)

		FetchContent_GetProperties(freetype)
		if(NOT freetype_POPULATED)
			FetchContent_Populate(freetype)
		endif()		
		set(FREETYPE_INC ${freetype_SOURCE_DIR}/include ${freetype_BINARY_DIR}/include PARENT_SCOPE)
		add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
	else()
		message(FATAL_ERROR "Freetype not found and downloading sources is disabled")
	endif()
endif()

find_package(Harfbuzz QUIET)
if(harfbuzz_FOUND)
	message(STATUS "Harfbuzz found")
else()
	if(DOWNLOAD_MISSING_DEPENDENCIES)
		message(STATUS "Harfbuzz not found, downloading sources")
		FetchContent_Declare(Harfbuzz
			GIT_REPOSITORY https://github.com/harfbuzz/harfbuzz.git
			GIT_TAG 2.6.1
		)

		FetchContent_GetProperties(Harfbuzz)
		if(NOT Harfbuzz_POPULATED)
			FetchContent_Populate(Harfbuzz)
		endif()		
		#set(FREETYPE_INC ${freetype_SOURCE_DIR}/include ${freetype_BINARY_DIR}/include PARENT_SCOPE)
		add_subdirectory(${harfbuzz_SOURCE_DIR} ${harfbuzz_BINARY_DIR})
	else()
		message(FATAL_ERROR "Harfbuzz not found and downloading sources is disabled")
	endif()
endif()

set(GLAD_INC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include PARENT_SCOPE)

FetchContent_Declare(cxxopts
	GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
	GIT_TAG v2.1.2
)

if(NOT cxxopts_POPULATED)
	FetchContent_Populate(cxxopts)
	set(CXXOPTS_INC ${cxxopts_SOURCE_DIR}/include PARENT_SCOPE)
endif()
