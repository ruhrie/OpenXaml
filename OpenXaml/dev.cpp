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
#include "Application.h"
using namespace std;
using namespace OpenXaml;
Font fa;
struct coordinate PixelScale;

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

	Application app = Application();
	app.Run();

	GLFWwindow *window;
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_VISIBLE, 0);
	window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);

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
	Frame frame = OpenXaml::Parser::ReadFile(inputFile);
	glfwSetWindowSize(window, frame.Width, frame.Height);
	PixelScale = coordinate({
		1.0f / frame.Width,
		1.0f / frame.Height
		});

	GLuint shader = GL::LoadShaders();

	frame.Initialize(shader);
	glfwShowWindow(window);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		frame.Draw();
		glfwSwapBuffers(window);

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glfwPollEvents();
	}

	glfwTerminate();
}