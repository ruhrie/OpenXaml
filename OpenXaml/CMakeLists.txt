add_subdirectory(Shaders)

file(GLOB SOURCES "Parser/*" "XamlObjects/*" "../Dependencies/glad/src/*" "GL/*") 
add_executable(dev "dev.cpp" ${SOURCES})

set (INCLUDE_DIRS {
	${ROOT_DIR}/Dependencies/glad/include/
	${ROOT_DIR}/Dependencies/xerces/src/
	${BIN_ROOT_DIR}/Dependencies/xerces/src/
	${CMAKE_CURRENT_SOURCE_DIR}/include/
	${ROOT_DIR}/Dependencies/freetype/include/
})
target_include_directories(dev PRIVATE ${INCLUDE_DIRS} )
target_link_libraries(dev xerces-c glfw freetype)


if(OPENGL_FOUND)
	target_link_libraries(dev ${OPENGL_gl_LIBRARY})
	target_include_directories(dev PRIVATE ${OPENGL_INCLUDE_DIR})
    if(OPENGL_GLU_FOUND)
		target_link_libraries(dev ${OPENGL_glu_LIBRARY})
    endif(OPENGL_GLU_FOUND)
endif(OPENGL_FOUND)


