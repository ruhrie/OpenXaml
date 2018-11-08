#include "GL/Font.h"
#include <iostream>
Font::Font(FT_Library lib, string file)
{
	auto error = FT_New_Face(lib, file.c_str(), 0, &face);
	if (error)
	{
		std::cerr << "Failed to open " << file << "\n";
	}
}