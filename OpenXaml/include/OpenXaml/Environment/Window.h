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
		};

		extern Window* window;
	}
}