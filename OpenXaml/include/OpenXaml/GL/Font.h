#pragma once
#include <string>
#include <map>
#include <vector>
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

struct UChar
{
	char32_t Character;
	double xOffset;
	double yOffset;
	double xAdvance;
	double yAdvance;
	unsigned int cluster;
};

///A wrapper for a font object
class Font
{
public:
	Font(std::string file, float size);
	Character &operator[](const char32_t index);
	int Height;
	std::map<unsigned int, GlyphBound> GlyphTextureMap;
	std::vector<UChar> FormatText(std::u32string input);
	bool IsSeperator(unsigned int charcode);
	bool IsNewLine(unsigned int charcode);
	~Font();

private:
	std::map<char32_t, Character> characterMap;
	unsigned int fontAtlasTexture;
	void *hbFont = NULL;
	unsigned int seperators[4];
};
} // namespace OpenXaml