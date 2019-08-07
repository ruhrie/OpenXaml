#pragma once
#include <string>
#include <map>
#include <ft2build.h>
#include "OpenXaml/GL/Character.h"
#include FT_FREETYPE_H

class Font
{
public:
	Font();
	Font(FT_Library lib, std::string file, float size);
	Character& operator[](const char index);
	int Height;
	~Font();
private:
	FT_Face face;
	std::map<char, Character> characterMap;
};