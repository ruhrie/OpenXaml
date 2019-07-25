#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "XamlObjects/Frame.h"
#include "GL/GLConfig.h"
#include "GL/Font.h"
#include "Application.h"
#include "MainPage.xaml.h"

using namespace std;
using namespace OpenXaml;

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
		//return EXIT_FAILURE;
	}
	MainPageInstance* inst = new MainPageInstance();
	Application app = Application();
	app.InitializeComponent(inst);
	app.Run();
}