#include "OpenXaml/Environment.h"
#include "OpenXaml/GL/Font.h"
#include <filesystem>
#include <iostream>
#include <GLFW/glfw3.h>
#include <algorithm>
using namespace OpenXaml;
using namespace std;

namespace OpenXaml
{
	namespace Environment
	{
		std::map < std::tuple<std::string, bool, bool>, std::vector<std::string> > fontFileMap;
		double DPI;
		std::map<FontProperties, Font*> fontMap;
		FT_Library fontLibrary;
		void LoadEnvironment()
		{
			FT_Init_FreeType(&fontLibrary);
			LoadFonts();
			GLFWmonitor* primary = glfwGetPrimaryMonitor();
			int widthMM, heightMM;
			glfwGetMonitorPhysicalSize(primary, &widthMM, &heightMM);
			const GLFWvidmode* mode = glfwGetVideoMode(primary);
			DPI = mode->width / (widthMM / 25.4);
		}

		void ClearEnvironment()
		{
			for (auto const& [key, val] : fontMap)
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
			fontDirectories.push_back("/usr/share/fonts");
			fontDirectories.push_back("/usr/local/share/fonts");
#else
			cerr << "Unrecognized platform. Loading no system fonts.\n";
#endif
			vector<string> validExtensions;
			validExtensions.push_back(".ttf");
			validExtensions.push_back(".TTF");
			validExtensions.push_back(".ttc");
			validExtensions.push_back(".otf");

			for (int i = 0; i < fontDirectories.size(); i++)
			{
				for (auto& entry : std::filesystem::recursive_directory_iterator(fontDirectories[i]))
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
					auto error = FT_New_Face(fontLibrary, file.c_str(), 0, &face);
					if (error)
					{
						std::cerr << "Failed to open " << file << "\n";
					}
					fontFileMap[{
						face->family_name,
							(face->style_flags& FT_STYLE_FLAG_BOLD) == FT_STYLE_FLAG_BOLD,
							(face->style_flags& FT_STYLE_FLAG_ITALIC) == FT_STYLE_FLAG_ITALIC
					}].push_back(file);

						FT_Done_Face(face);
				}
			}
		}

		Font* GetFont(FontProperties prop)
		{
			auto index = fontMap.find(prop);
			if (index == fontMap.end())
			{
				auto fileIndex = fontFileMap.find({ prop.name, prop.bold, prop.italic });
				if (fileIndex == fontFileMap.end())
				{
					cerr << "Failed to find font " << prop.name << " Bold:" << prop.bold << " Italic:" << prop.italic << "\n";
					return NULL;
				}
				vector<string> fontFiles = fontFileMap[{prop.name, prop.bold, prop.italic}];
				fontMap[prop] = new Font(fontLibrary, fontFiles[0], prop.size);
			}
			return fontMap[prop];
		}
	}
}