add_subdirectory(Shaders)

file(GLOB SOURCES "Parser/*" "XamlObjects/*" "../Dependencies/glad/src/*" "GL/*" "*") 
add_executable(dev "dev.cpp" ${SOURCES})

set (INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/ )
target_include_directories(dev PRIVATE ${INCLUDE_DIRS} ${XERCES_INC} ${FREETYPE_INC} ${GLAD_INC} ${GLFW_INC})
target_link_libraries(dev xerces-c glfw freetype)


if(OPENGL_FOUND)
	target_link_libraries(dev ${OPENGL_gl_LIBRARY})
	target_include_directories(dev PRIVATE ${OPENGL_INCLUDE_DIR})
    if(OPENGL_GLU_FOUND)
		target_link_libraries(dev ${OPENGL_glu_LIBRARY})
    endif(OPENGL_GLU_FOUND)
endif(OPENGL_FOUND)


