#pragma once
#include "OpenXaml/XamlObjects/Frame.h"
#include "OpenXaml/XamlObjects/Coordinate.h"

namespace OpenXaml
{
	class Application
	{
	public:
		Application();
		~Application();
		void Run();
		void InitializeComponent(Frame* frame);
	private:
		Frame* frame;
		coordinate PixelScale;
	};
}