#pragma once
#include <map>
#include <vector>
#include <string>
#include "GL/Font.h"
#include "GL/FontProperties.h"
namespace OpenXaml
{
	namespace Environment
	{
		void LoadFonts();
		extern std::map < std::tuple<std::string, bool, bool>, std::vector<std::string> > fontFileMap;
		extern double DPI;
		Font* GetFont(FontProperties prop);
		void LoadEnvironment();
		void ClearEnvironment();
	}
}
