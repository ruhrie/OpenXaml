add_subdirectory("Parser")

set(INCLUDE_SRC ${PARSER_SRC})

add_executable(GLFWHelloWorld "GLFWHelloWorld.cpp")
add_executable(dev "dev.cpp" ${INCLUDE_SRC})

set (INCLUDE_DIRS {
	${ROOT_DIR}/Dependencies/xerces/src
	${BIN_ROOT_DIR}/Dependencies/xerces/src/
	${CMAKE_CURRENT_SOURCE_DIR}/include
})

target_include_directories(dev PRIVATE ${INCLUDE_DIRS})
target_link_libraries(dev "xerces-c")

target_link_libraries(GLFWHelloWorld glfw)

if(OPENGL_FOUND)
    target_link_libraries(GLFWHelloWorld ${OPENGL_gl_LIBRARY})
    target_include_directories(GLFWHelloWorld PRIVATE ${OPENGL_INCLUDE_DIR})
    if(OPENGL_GLU_FOUND)
        target_link_libraries(GLFWHelloWorld ${OPENGL_glu_LIBRARY})
    endif(OPENGL_GLU_FOUND)
	target_link_libraries(dev ${OPENGL_gl_LIBRARY})
    target_include_directories(dev PRIVATE ${OPENGL_INCLUDE_DIR})
endif(OPENGL_FOUND)
