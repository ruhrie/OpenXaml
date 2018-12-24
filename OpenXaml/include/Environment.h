#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <map>
#include <vector>
#include <string>
#include "GL/Font.h"
namespace OpenXaml
{
    class Environment
    {
    public:
        Environment();
        ~Environment();
        void GetFont(string fontName, Font &font);
    private:
        void LoadFonts();
        FT_Library fontLibrary;
        map<string, vector<string>> fontFileMap;
        map<string, Font> fontMap;
    };
    extern "C" Environment env;
}

#endif