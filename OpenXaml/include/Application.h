#ifndef APPLICATION_H
#define APPLICATION_H
#include "GL/Font.h"
#include <vector>
#include <map>
#include <string>

namespace OpenXaml
{
	class Application
	{
	public:
		Application();
		~Application();
	private:
		FT_Library fontLibrary;
		void GetFonts();
		map<string, vector<string>> fontFileMap;
	};
}

#endif