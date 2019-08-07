#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenXaml/XamlObjects/Frame.h"
#include "OpenXaml/Application.h"
#include "MainPage.xaml.h"

using namespace std;
using namespace OpenXaml;

int main()
{
	MainPageInstance* inst = new MainPageInstance();
	Application app = Application();
	app.InitializeComponent(inst);
	app.Run();
}