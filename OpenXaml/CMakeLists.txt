add_executable(GLFWHelloWorld "GLFWHelloWorld.cpp")

target_link_libraries(GLFWHelloWorld glfw)
if(OPENGL_FOUND)
    target_link_libraries(GLFWHelloWorld ${OPENGL_gl_LIBRARY})
    #target_include_directories(GLFWHelloWorld ${OPENGL_INCLUDE_DIR})
endif(OPENGL_FOUND)


