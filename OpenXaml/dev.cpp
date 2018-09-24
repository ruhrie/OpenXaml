#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Parser/Parser.h"
#include "XamlObjects/XamlObject.h"
#include <GLFW/glfw3.h>
#include "XamlObjects/Frame.h"

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
	Frame *contents = OpenXaml::Parser::ReadFile(inputFile);
	window = glfwCreateWindow(contents->Width, contents->Height, "My Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		contents->Draw();
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	
	
	

	
	cout << argv[0];
	cout << "done";
}