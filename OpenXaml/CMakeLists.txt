
find_package(OpenGL REQUIRED)
find_package(Vulkan)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/fragment.glsl" FRAGMENT_CODE)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/vertex.glsl" VERTEX_CODE)
configure_file("GL/GLConfig.cpp.in" "GL/GLConfig.cpp")

file(GLOB SOURCES "XamlObjects/*.cpp" "../Dependencies/glad/src/*.c" "GL/*.cpp" "*.cpp" "XamlEvents/*.cpp" "Environment/*.cpp")

set (OPENXAML_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/" PARENT_SCOPE)
set (LOCAL_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set (OPENGL_INC "")
set (VULKAN_INC "")
set (LIBRARIES glfw freetype)
if (UNIX)
	set(LIBRARIES ${LIBRARIES} "-lstdc++fs")
endif(UNIX)

if(OPENGL_FOUND)
	set (LIBRARIES ${LIBRARIES} ${OPENGL_gl_LIBRARY})
	set (OPENGL_INC ${OPENGL_INCLUDE_DIR})
	add_compile_definitions("OPENGL")
endif(OPENGL_FOUND)

if(Vulkan_FOUND)
    set (LIBRARIES ${LIBRARIES} ${Vulkan_LIBRARIES})
    set(VULKAN_INC ${Vulkan_INCLUDE_DIRS})
    add_compile_definitions("VULKAN")
endif(Vulkan_FOUND)
add_library(OpenXaml STATIC ${SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/GL/GLConfig.cpp")
set_target_properties(OpenXaml 
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
target_include_directories(OpenXaml PRIVATE ${LOCAL_INC} ${FREETYPE_INC} ${GLAD_INC} ${GLFW_INC} ${OPENGL_INC})
target_link_libraries(OpenXaml ${LIBRARIES})


#add_library(OpenXamlStatic STATIC ${SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/GL/GLConfig.cpp")

file(GLOB HEADERS "include/OpenXaml")

install(TARGETS OpenXaml EXPORT OpenXaml DESTINATION "lib")
install(DIRECTORY ${HEADERS} DESTINATION "include")











