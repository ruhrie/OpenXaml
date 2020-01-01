#pragma once

namespace OpenXaml
{
	namespace Environment
	{
		class Window
		{
		public:
			float width = 0;
			float height = 0;
		};

		extern Window* window;
	}
}