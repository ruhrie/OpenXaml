#include "MainPage.xaml.h"
#include <iostream>
void MainPageInstance::Test(std::shared_ptr<OpenXaml::Objects::XamlObject> sender)
{
    std::cout << "Pushed\n";
}