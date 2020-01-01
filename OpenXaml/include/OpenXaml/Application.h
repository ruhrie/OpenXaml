#pragma once
#include "OpenXaml/XamlObjects/Frame.h"
#include "OpenXaml/XamlObjects/vec2.h"
#include <memory>
namespace OpenXaml
{
    ///A singleton responsible for handling the OpenGL scope
    class Application
    {
    public:
        Application();
        ~Application();
        void Run();
        void InitializeComponent(std::shared_ptr<Objects::Frame> frame);

    private:
        std::shared_ptr<Objects::Frame> frame;
        vec2<float> PixelScale;
    };
} // namespace OpenXaml