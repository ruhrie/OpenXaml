#pragma once

namespace OpenXaml
{
	namespace Environment
	{
		class Window
		{
		public:
			float xScale = 0.0f;
			float yScale = 0.0f;
			unsigned int width = 0;
			unsigned int height = 0;
		};

		extern Window* window;
	}
}