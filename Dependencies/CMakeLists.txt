include(FetchContent)

FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)  
endif()
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INC ${glfw_SOURCE_DIR}/include ${glfw_BINARY_DIR}/include PARENT_SCOPE)
add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})

FetchContent_Declare(xerces
    URL https://www-eu.apache.org/dist//xerces/c/3/sources/xerces-c-3.2.2.tar.gz
    URL_HASH SHA256=dd6191f8aa256d3b4686b64b0544eea2b450d98b4254996ffdfe630e0c610413
)
FetchContent_GetProperties(xerces)
if(NOT xerces_POPULATED)
    FetchContent_Populate(xerces)
endif()
set(XERCES_INC ${xerces_SOURCE_DIR}/src ${xerces_BINARY_DIR}/src PARENT_SCOPE)
set(DISABLE_TESTS ON)
set(DISABLE_DOC ON)
set(DISABLE_SAMPLES ON)
add_subdirectory(${xerces_SOURCE_DIR} ${xerces_BINARY_DIR})

FetchContent_Declare(Freetype
    URL https://download.savannah.gnu.org/releases/freetype/freetype-2.10.0.tar.gz
)

FetchContent_GetProperties(freetype)
if(NOT freetype_POPULATED)
    FetchContent_Populate(freetype)
endif()		
add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
set(FREETYPE_INCLUDE_DIR_ft2build ${freetype_BINARY_DIR}/include)
set(FREETYPE_INCLUDE_DIR_freetype2 ${freetype_SOURCE_DIR}/include)
set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR_ft2build} ${FREETYPE_INCLUDE_DIR_freetype2}  PARENT_SCOPE)
set(FREETYPE_LIBRARY "freetype")

FetchContent_Declare(harfbuzz
    URL https://github.com/harfbuzz/harfbuzz/archive/2.6.1.tar.gz
)

set(HB_HAVE_FREETYPE ON CACHE STRING "" FORCE)
FetchContent_GetProperties(harfbuzz)
if(NOT harfbuzz_POPULATED)
    FetchContent_Populate(harfbuzz)
endif()		
add_subdirectory(${harfbuzz_SOURCE_DIR} ${harfbuzz_BINARY_DIR})
set(HARFBUZZ_INC ${harfbuzz_SOURCE_DIR}/src PARENT_SCOPE)

message(STATUS ${HARFBUZZ_INC})

set(GLAD_INC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include PARENT_SCOPE)

set(DEP_INC ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
