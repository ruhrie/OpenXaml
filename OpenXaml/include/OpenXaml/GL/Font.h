#pragma once
#include "OpenXaml/GL/Character.h"
#include <map>
#include <string>
#include <vector>
namespace OpenXaml
{
    struct GlyphBound
    {
        float txMin;
        float txMax;
        float tyMin;
        float tyMax;
        float width;
        float height;
        float xBearingH;
        float yBearingH;
    };

    struct UChar
    {
        uint32_t Character;
        float xOffset;
        float yOffset;
        float xAdvance;
        float yAdvance;
        unsigned int cluster;
    };

    ///A wrapper for a font object
    class Font
    {
    public:
        Font(std::string file, float size);
        Character &operator[](const char32_t index);
        int Height;
        int VerticalOffset;
        std::map<unsigned int, GlyphBound> GlyphMap;
        std::vector<UChar> FormatText(std::u32string input);
        bool IsSeperator(unsigned int charcode);
        bool IsNewLine(unsigned int charcode);
        ~Font();
        unsigned int getFontAtlasTexture();

    private:
        std::map<char32_t, Character> characterMap;
        unsigned int fontAtlasTexture;
        void *hbFont = NULL;
        unsigned int seperators[4];
    };
} // namespace OpenXaml