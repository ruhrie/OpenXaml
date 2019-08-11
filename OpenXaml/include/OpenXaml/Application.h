#pragma once
#include "OpenXaml/XamlObjects/Frame.h"
#include "OpenXaml/XamlObjects/Coordinate.h"

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
		coordinate PixelScale;
	};
}