include(FetchContent)

FetchContent_Declare(glfw
    URL https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
  FetchContent_Populate(glfw)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_INC ${glfw_SOURCE_DIR}/include ${glfw_BINARY_DIR}/include PARENT_SCOPE)
  add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_Declare(xerces
    URL https://www-eu.apache.org/dist//xerces/c/3/sources/xerces-c-3.2.2.tar.gz
    URL_HASH SHA256=dd6191f8aa256d3b4686b64b0544eea2b450d98b4254996ffdfe630e0c610413
)

FetchContent_GetProperties(xerces)
if(NOT xerces_POPULATED)
  FetchContent_Populate(xerces)
  set(XERCES_INC ${xerces_SOURCE_DIR}/src ${xerces_BINARY_DIR}/src PARENT_SCOPE)
  add_subdirectory(${xerces_SOURCE_DIR} ${xerces_BINARY_DIR})
endif()

FetchContent_Declare(Freetype
    URL https://download.savannah.gnu.org/releases/freetype/freetype-2.9.tar.gz    
)

FetchContent_GetProperties(freetype)
if(NOT freetype_POPULATED)
  FetchContent_Populate(freetype)
  set(FREETYPE_INC ${freetype_SOURCE_DIR}/include ${freetype_BINARY_DIR}/include PARENT_SCOPE)
  add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
endif()

set(GLAD_INC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include PARENT_SCOPE)