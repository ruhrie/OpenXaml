set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("glfw")
include_directories("glfw/include")

add_subdirectory("xerces")
include_directories("xerces/src")

add_subdirectory("freetype")
include_directories("freetype/include")

include_directories("glad/include")