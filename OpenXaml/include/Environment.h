#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <map>
#include <vector>
#include <string>
#include "GL/Font.h"
#include "GL/FontProperties.h"
namespace OpenXaml
{
    class Environment
    {
    public:
        Environment();
        ~Environment();
        Font* GetFont(FontProperties prop);
		double getDPI();
		void Initialize();
    private:
        void LoadFonts();
        FT_Library fontLibrary;
		map < std::tuple<std::string, bool, bool>, vector<string> > fontFileMap;
		map<FontProperties, Font*> fontMap;
		double DPI;
    };
    extern "C" Environment env;
}

#endif