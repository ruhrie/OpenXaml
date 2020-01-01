#include "MainPage.xaml.h"
#include "OpenXaml/Application.h"
#include "OpenXaml/XamlObjects/Frame.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>

using namespace std;
using namespace OpenXaml;

int main()
{
    shared_ptr<MainPageInstance> inst = make_shared<MainPageInstance>();
    Application app = Application();
    app.InitializeComponent(inst);
    app.Run();
}