#pragma once
#include "OpenXaml/XamlObjects/Frame.h"
#include "OpenXaml/XamlObjects/vec2.h"

namespace OpenXaml
{
	///A singleton responsible for handling the OpenGL scope
	class Application
	{
	public:
		Application();
		~Application();
		void Run();
		void InitializeComponent(Objects::Frame* frame);
	private:
		Objects::Frame* frame;
		vec2<float> PixelScale;
	};
}