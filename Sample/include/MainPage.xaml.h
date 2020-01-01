#pragma once
#include "MainPage.hpp"
#include <memory>
class MainPageInstance : public MainPage
{
public:
    void Test(std::shared_ptr<OpenXaml::Objects::XamlObject> source);
};