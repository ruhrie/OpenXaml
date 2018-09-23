file(GLOB SOURCES "Parser/*" "XamlObjects/*")

add_executable(GLFWHelloWorld "GLFWHelloWorld.cpp")
add_executable(dev "dev.cpp" ${SOURCES})

set (INCLUDE_DIRS {
	${ROOT_DIR}/Dependencies/xerces/src
	${BIN_ROOT_DIR}/Dependencies/xerces/src/
	${CMAKE_CURRENT_SOURCE_DIR}/include
})

target_include_directories(dev PRIVATE ${INCLUDE_DIRS})
target_link_libraries(dev xerces-c glfw)

target_link_libraries(GLFWHelloWorld glfw)

if(OPENGL_FOUND)
	target_link_libraries(dev ${OPENGL_gl_LIBRARY})
	target_include_directories(dev PRIVATE ${OPENGL_INCLUDE_DIR})
    target_link_libraries(GLFWHelloWorld ${OPENGL_gl_LIBRARY})
    target_include_directories(GLFWHelloWorld PRIVATE ${OPENGL_INCLUDE_DIR})
    if(OPENGL_GLU_FOUND)
        target_link_libraries(GLFWHelloWorld ${OPENGL_glu_LIBRARY})
		target_link_libraries(dev ${OPENGL_glu_LIBRARY})
    endif(OPENGL_GLU_FOUND)
endif(OPENGL_FOUND)
