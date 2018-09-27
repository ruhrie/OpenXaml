#ifndef GLC
#define GLC
#include <glad/glad.h>
namespace GL
{
	void InizializeOpenGL();

	GLuint LoadShaders();

	static GLuint vertexBuffer;

	static GLuint shaderProgram;
}

#endif