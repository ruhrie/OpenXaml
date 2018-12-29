project("OpenXaml" 
)

set (CMAKE_CXX_STANDARD 17)

find_package( OpenGL REQUIRED )

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/fragment.glsl" FRAGMENT_CODE)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/vertex.glsl" VERTEX_CODE)
configure_file("GL/GLConfig.cpp.in" "GL/GLConfig.cpp")

file(GLOB SOURCES "Parser/*.cpp" "XamlObjects/*.cpp" "../Dependencies/glad/src/*.c" "GL/*.cpp" "*.cpp")
add_library(OpenXaml ${SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/GL/GLConfig.cpp")
set_target_properties(OpenXaml 
	PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

set (OPENXAML_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/" PARENT_SCOPE)
set (LOCAL_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories(OpenXaml PRIVATE ${LOCAL_INC} ${XERCES_INC} ${FREETYPE_INC} ${GLAD_INC} ${GLFW_INC})
target_link_libraries(OpenXaml xerces-c glfw freetype)



if(OPENGL_FOUND)
	target_link_libraries(OpenXaml ${OPENGL_gl_LIBRARY})
	target_include_directories(OpenXaml PRIVATE ${OPENGL_INCLUDE_DIR})
    if(OPENGL_GLU_FOUND)
		target_link_libraries(OpenXaml ${OPENGL_glu_LIBRARY})
    endif(OPENGL_GLU_FOUND)
endif(OPENGL_FOUND)