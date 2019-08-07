#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
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