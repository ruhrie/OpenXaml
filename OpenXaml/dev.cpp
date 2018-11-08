#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Parser/Parser.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "XamlObjects/Frame.h"
#include "GL/GLConfig.h"
#include "GL/Font.h"
#include "Globals.h"
using namespace std;

Font fa;

int main(int argc, char *argv[], char *envp[])
{
	std::string inputFile;
	for (int i = 1; i < argc; i++)
	{
		string parameter(argv[i]);
		if (parameter == "-i")
		{
			inputFile = argv[++i];
		}
		else
		{
			cerr << "Unrecognized input parameter: " << argv[i] << "\n";
			return EXIT_FAILURE;
		}
	}
	bool error = false;
	if (inputFile == "")
	{
		cerr << "Input file is required\n";
		error = true;
	}
	if (error)
	{
		return EXIT_FAILURE;
	}


	GLFWwindow *window;
	if (!glfwInit())
		return -1;

	Frame frame = OpenXaml::Parser::ReadFile(inputFile);
	window = glfwCreateWindow(frame.Width, frame.Height, "My Window", NULL, NULL);
	frame.SetScale(1.0f / frame.Width, true);
	frame.SetScale(1.0f / frame.Height, false);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) /* There was an error initilizing GLAD */
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}
	FT_Library fontLibrary;
	FT_Init_FreeType(&fontLibrary);
	Font font = Font(fontLibrary, "C:\\Arimo-Regular.ttf", 24);
	auto hi = font['a'];
	auto hio = font['a'];
	GLuint shader = GL::LoadShaders();
	fa = font;
	GLint posAttrib = glGetAttribLocation(shader, "position");	

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	
	
	frame.Initialize(shader);

	//glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(0);

	//https://stackoverflow.com/questions/34068792/drawing-multiple-objects-in-opengl-with-different-buffers

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(posAttrib);
		frame.Draw();		
		
		//glUseProgram(shader);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		glViewport(0, 0, width, height);
		
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	
	cout << "done";
}