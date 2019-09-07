#pragma once
#include <map>
#include <vector>
#include <string>
#include "OpenXaml/GL/Font.h"
#include "OpenXaml/GL/FontProperties.h"
namespace OpenXaml
{
	namespace Environment
	{
		void LoadFonts(); ///Loads font files from the system
		extern std::map < std::tuple<std::string, bool, bool>, std::vector<std::string> > fontFileMap; ///A map from file properties to the path
		extern double DPI;
		Font* GetFont(FontProperties prop); //Gets a font object from the desired properties
		void LoadEnvironment(); ///Initializes environment variables
		void ClearEnvironment(); ///Releases environment resources
	}
}
