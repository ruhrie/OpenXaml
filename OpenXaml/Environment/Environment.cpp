#include "OpenXaml/Environment/Environment.h"
#include "OpenXaml/Environment/Window.h"
#include "OpenXaml/GL/Font.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <filesystem>
#include <ft2build.h>
#include <iostream>
#include FT_FREETYPE_H
using namespace OpenXaml;
using namespace std;

namespace OpenXaml::Environment
{
    Objects::XamlObject *ActiveElement;
    std::map<std::tuple<std::string, bool, bool>, std::vector<std::string>> fontFileMap;
    double DPI;
    std::map<FontProperties, Font *> fontMap;
    FT_Library fontLibrary;
    void LoadEnvironment()
    {
        FT_Init_FreeType(&fontLibrary);
        LoadFonts();
        UpdateWindow();
    }
    void UpdateWindow()
    {
        GLFWmonitor *primary = glfwGetPrimaryMonitor();
        int widthMM;
        int heightMM;
        glfwGetMonitorPhysicalSize(primary, &widthMM, &heightMM);
        const GLFWvidmode *mode = glfwGetVideoMode(primary);
        DPI = mode->width / (widthMM / 25.4);
    }

    void ClearEnvironment()
    {
        for (auto const &[key, val] : fontMap)
        {
            delete val;
        }
        FT_Done_FreeType(fontLibrary);
    }

    void LoadFonts()
    {
        vector<string> fontDirectories;
        vector<string> fontFiles;
        fontFiles.clear();
#if _WIN32
        fontDirectories.push_back("C:\\Windows\\Fonts");
#elif __linux__
        fontDirectories.emplace_back("/usr/share/fonts");
        fontDirectories.emplace_back("/usr/local/share/fonts");
#else
        cerr << "Unrecognized platform. Loading no system fonts.\n";
#endif
        vector<string> validExtensions;
        validExtensions.emplace_back(".ttf");
        validExtensions.emplace_back(".TTF");
        validExtensions.emplace_back(".ttc");
        validExtensions.emplace_back(".otf");

        for (auto &fontDirectorie : fontDirectories)
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(fontDirectorie))
            {
                if (std::filesystem::is_regular_file(entry))
                {
                    if (find(validExtensions.begin(), validExtensions.end(), entry.path().extension().string()) != validExtensions.end())
                    {
                        fontFiles.push_back(entry.path().string());
                    }
                }
            }
        }
        fontFileMap.clear();

        for (const auto &file : fontFiles)
        {
            bool correct = false;
            for (const auto &extension : validExtensions)
            {
                correct = 0 == file.compare(file.length() - extension.length(), extension.length(), extension);
                if (correct)
                {
                    break;
                }
            }
            if (correct)
            {
                FT_Face face;
                auto error = FT_New_Face(fontLibrary, file.c_str(), 0, &face);
                if (error != 0)
                {
                    std::cerr << "Failed to open " << file << "\n";
                }
                fontFileMap[{
                                face->family_name,
                                (face->style_flags & FT_STYLE_FLAG_BOLD) == FT_STYLE_FLAG_BOLD,
                                (face->style_flags & FT_STYLE_FLAG_ITALIC) == FT_STYLE_FLAG_ITALIC}]
                    .push_back(file);

                FT_Done_Face(face);
            }
        }
    }

    Font *GetFont(const FontProperties &prop)
    {
        auto index = fontMap.find(prop);
        if (index == fontMap.end())
        {
            auto fileIndex = fontFileMap.find({prop.name, prop.bold, prop.italic});
            if (fileIndex == fontFileMap.end())
            {
                cerr << "Failed to find font " << prop.name << " Bold:" << prop.bold << " Italic:" << prop.italic << "\n";
                return nullptr;
            }
            vector<string> fontFiles = fontFileMap[{prop.name, prop.bold, prop.italic}];
            fontMap[prop] = new Font(fontFiles[0], prop.size);
        }
        return fontMap[prop];
    }
} // namespace OpenXaml::Environment