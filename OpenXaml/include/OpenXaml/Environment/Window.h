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
			float width = 0;
			float height = 0;
		};

		extern Window* window;
	}
}