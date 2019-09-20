#pragma once
#include <string>
#include <map>
#include "OpenXaml/GL/Character.h"
namespace OpenXaml
{
	struct GlyphBound
	{
		float xMin;
		float xMax;
		float yMin;
		float yMax;
	};
	///A wrapper for a font object
	class Font
	{
	public:
		Font(std::string file, float size);
		Character& operator[](const char32_t index);
		int Height;
		std::map<char32_t, GlyphBound> GlyphTextureMap; 
		~Font();
	private:
		std::map<char32_t, Character> characterMap;
		unsigned int fontAtlasTexture;
	};
}