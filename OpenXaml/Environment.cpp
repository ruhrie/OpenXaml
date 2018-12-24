#include "Environment.h"
#include "GL/Font.h"
#include <filesystem>
#include <iostream>
using namespace OpenXaml;
using namespace std;
Environment::Environment()
{
    FT_Init_FreeType(&(Environment::fontLibrary));
    LoadFonts();
}

Environment::~Environment()
{
    FT_Done_FreeType(Environment::fontLibrary);
}

void Environment::LoadFonts()
{
    vector<string> fontDirectories;
    vector<string> fontFiles;
#if _WIN32
    fontDirectories.push_back("C:\\Windows\\Fonts");
#elif __linux__
    fontDirectories.push_back("/usr/share/fonts");
    fontDirectories.push_back("/usr/local/share/fonts");
#else
    cerr << "Unrecognized platform. Loading no system fonts.\n";
#endif

    for (int i = 0; i < fontDirectories.size(); i++)
    {
        for (const auto &entry : std::filesystem::directory_iterator(fontDirectories[i]))
        {
            fontFiles.push_back(entry.path().string());
        }
    }
    fontFileMap.clear();
    vector<string> validExtensions;
    validExtensions.push_back(".ttf");
    validExtensions.push_back(".TTF");
    validExtensions.push_back(".ttc");
    validExtensions.push_back(".otf");
    for (int i = 0; i < fontFiles.size(); i++)
    {
        string file = fontFiles[i];
        bool correct = false;
        for (int j = 0; j < validExtensions.size(); j++)
        {
            string extension = validExtensions[j];
            correct = 0 == file.compare(file.length() - extension.length(), extension.length(), extension);
            if (correct)
            {
                break;
            }
        }
        if (correct)
        {
            FT_Face face;
            auto error = FT_New_Face(Environment::fontLibrary, file.c_str(), 0, &face);
            if (error)
            {
                std::cerr << "Failed to open " << file << "\n";
            }
            fontFileMap[face->family_name].push_back(file);
            FT_Done_Face(face);
        }
    }
}

void Environment::GetFont(string fontName, Font &font)
{
    auto local = fontMap.find(fontName);
    if (local != fontMap.end())
    {
        font = fontMap[fontName];
        return;
    }
    fontMap[fontName] = Font();
}