#ifndef APPLICATION_H
#define APPLICATION_H
#include "GL/Font.h"
#include <vector>
#include <map>
#include <string>
#include <GLFW/glfw3.h>

namespace OpenXaml
{
	class Application
	{
	public:
		Application();
		~Application();
		void Run();
	private:
		FT_Library fontLibrary;
		void GetFonts();
		map<string, vector<string>> fontFileMap;
		GLFWwindow *window;
	};
}

#endif