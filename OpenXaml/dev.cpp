#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Parser/Parser.h"
#include "XamlObjects/XamlObject.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "XamlObjects/Frame.h"
#include "GL/GLConfig.h"

using namespace std;



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

	GLuint shader = GL::LoadShaders();
	
	//glBindBuffer(GL_ARRAY_BUFFER, GL::vertexBuffer);
	
	GLint posAttrib = glGetAttribLocation(shader, "position");	
	
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glUseProgram(shader);

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		
		glClear(GL_COLOR_BUFFER_BIT);

		frame.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	
	
	

	
	cout << argv[0];
	cout << "done";
}