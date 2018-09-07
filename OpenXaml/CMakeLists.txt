add_executable(GLFWHelloWorld "GLFWHelloWorld.cpp")

target_link_libraries(GLFWHelloWorld glfw)
if(OPENGL_FOUND)
    target_link_libraries(GLFWHelloWorld ${OPENGL_gl_LIBRARY})
    target_include_directories(GLFWHelloWorld PRIVATE ${OPENGL_INCLUDE_DIR})
    if(OPENGL_GLU_FOUND)
        target_link_libraries(GLFWHelloWorld ${OPENGL_glu_LIBRARY})
    endif(OPENGL_GLU_FOUND)
endif(OPENGL_FOUND)


