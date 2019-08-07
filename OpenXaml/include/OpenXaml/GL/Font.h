#pragma once
#include <string>
#include <map>
#include "OpenXaml/GL/Character.h"

class Font
{
public:
	Font();
	Font(std::string file, float size);
	Character& operator[](const char index);
	int Height;
	~Font();
private:
	std::map<char, Character> characterMap;
};