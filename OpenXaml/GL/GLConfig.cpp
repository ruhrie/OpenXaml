#include "GL/GLConfig.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
namespace GL
{
	GLuint LoadShaders()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		string fragment;
		string vertex;
		ifstream fragmentFile("Shaders/fragment.glsl");
		string line;
		while (getline(fragmentFile, line))
		{
			fragment += line + "\n";
		}
		fragmentFile.close();
		ifstream vertexFile("Shaders/vertex.glsl");
		while (getline(vertexFile, line))
		{
			vertex += line + "\n";
		}
		vertexFile.close();

		const char * vertexsrc = vertex.c_str();
		const char * fragmentsrc = fragment.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexsrc, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentsrc, NULL);
		glCompileShader(fragmentShader);

		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glBindFragDataLocation(shaderProgram, 0, "outColor");
		glLinkProgram(shaderProgram);

		return shaderProgram;
	}
}
