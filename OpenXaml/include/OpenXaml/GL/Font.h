#pragma once
#include <string>
#include <map>
#include "OpenXaml/GL/Character.h"
namespace OpenXaml
{
	///A wrapper for a font object
	class Font
	{
	public:
		Font(std::string file, float size);
		Character& operator[](const char index);
		int Height;
		~Font();
	private:
		std::map<char, Character> characterMap;
	};
}