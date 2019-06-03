project("OpenXaml" 
)

set (CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(Vulkan)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/fragment.glsl" FRAGMENT_CODE)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/vertex.glsl" VERTEX_CODE)
configure_file("GL/GLConfig.cpp.in" "GL/GLConfig.cpp")

file(GLOB SOURCES "Parser/*.cpp" "XamlObjects/*.cpp" "../Dependencies/glad/src/*.c" "GL/*.cpp" "*.cpp" "XamlEvents/*.cpp")
add_library(OpenXaml ${SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/GL/GLConfig.cpp")
set_target_properties(OpenXaml 
	PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

set (OPENXAML_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/" PARENT_SCOPE)
set (LOCAL_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_include_directories(OpenXaml PRIVATE ${XERCES_INC} ${LOCAL_INC} ${FREETYPE_INC} ${GLAD_INC} ${GLFW_INC} ${SIGNALS_INC})

if (UNIX)
	target_link_libraries(OpenXaml xerces-c glfw freetype signals "-lstdc++fs")
else()
    target_link_libraries(OpenXaml xerces-c glfw freetype signals)
endif(UNIX)

if(OPENGL_FOUND)
	target_link_libraries(OpenXaml ${OPENGL_gl_LIBRARY})
	target_include_directories(OpenXaml PRIVATE ${OPENGL_INCLUDE_DIR})
	add_compile_definitions("OPENGL")
endif(OPENGL_FOUND)

if(Vulkan_FOUND)
    target_link_libraries(OpenXaml ${Vulkan_LIBRARIES})
    target_include_directories(OpenXaml PRIVATE ${Vulkan_INCLUDE_DIRS})
    add_compile_definitions("VULKAN")
endif(Vulkan_FOUND)