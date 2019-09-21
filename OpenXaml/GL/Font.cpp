#include "OpenXaml/GL/Font.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "OpenXaml/Environment/Environment.h"
#include <glad/glad.h>
#include <ft2build.h>
#include <algorithm>
#include <hb.h>
#include <hb-ft.h>
#include FT_FREETYPE_H

using namespace std;

namespace OpenXaml
{
namespace Environment
{
//I don't like doing this in a cpp, but it was that or a private header
extern FT_Library fontLibrary;
} // namespace Environment
std::map<Font *, FT_Face> faceMap;

Font::Font(string file, float size)
{
	// load the font from the file at the given size
	FT_Face newFace;
	auto error = FT_New_Face(OpenXaml::Environment::fontLibrary, file.c_str(), 0, &newFace);
	if (error)
	{
		std::cerr << "Failed to open " << file << "\n";
		return;
	}
	double dpi = OpenXaml::Environment::DPI;
	FT_Set_Char_Size(newFace, 0, (int)(size * 64), (int)dpi, (int)dpi);
	Height = newFace->size->metrics.height;
	faceMap[this] = newFace;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/* testing here */

	FT_UInt gindex;
	FT_ULong charcode;
	charcode = FT_Get_First_Char(newFace, &gindex);
	unsigned int maxHeight = 0;
	unsigned int maxWidth = 0;
	unsigned int numChars = 0;

	while (gindex != 0)
	{
		auto error = FT_Load_Glyph(newFace, gindex, FT_LOAD_DEFAULT);
		if (error)
		{
			std::cerr << "Failed to load " << gindex << "\n";
		}
		else
		{
			maxHeight = std::max(maxHeight, newFace->glyph->bitmap.rows);
			maxWidth = std::max(maxWidth, newFace->glyph->bitmap.width);
			numChars++;
		}
		charcode = FT_Get_Next_Char(newFace, charcode, &gindex);
	}

	charcode = FT_Get_First_Char(newFace, &gindex);

	float sides = ceil(sqrt(numChars));
	int width = sides * maxWidth;
	int height = ceil(numChars / sides) * maxHeight;
	uint8_t *fontAtlas = (uint8_t *)calloc(width * height, sizeof(uint8_t));
	int x = 0;
	int y = 0;
	while (gindex != 0)
	{
		auto error = FT_Load_Glyph(newFace, gindex, FT_LOAD_DEFAULT);
		if (error)
		{
			std::cerr << "Failed to load " << gindex << "\n";
		}
		error = FT_Render_Glyph(newFace->glyph, FT_RENDER_MODE_NORMAL);
		if (error)
		{
			std::cerr << "Failed to render " << gindex << "\n";
		}
		int bx = newFace->glyph->bitmap.width;
		int by = newFace->glyph->bitmap.rows;
		for (int j = 0; j < by; j++)
		{
			memcpy(fontAtlas + j * width + x * maxWidth + y * width * maxHeight, newFace->glyph->bitmap.buffer + j * bx, bx);
		}

		auto bound = GlyphBound{
			2.0f * (float)(x * maxWidth) / (float)width - 1.0f,
			2.0f * (float)((x * maxWidth) + bx) / (float)width - 1.0f,
			2.0f * (float)(y * maxHeight) / (float)height - 1.0f,
			2.0f * (float)(y * maxHeight + by) / (float)height - 1.0f};
		GlyphTextureMap[newFace->glyph->glyph_index] = bound;
		if (++x > width / maxWidth)
		{
			x = 0;
			y++;
		}
		charcode = FT_Get_Next_Char(newFace, charcode, &gindex);
	}

	glGenTextures(1, &fontAtlasTexture);
	glBindTexture(GL_TEXTURE_2D, fontAtlasTexture);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		width,
		height,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		fontAtlas);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	free(fontAtlas);

	hbFont = hb_ft_font_create_referenced(newFace);
}
Character &Font::operator[](const char32_t index)
{
	// if the character is available return it
	if (characterMap.find(index) != characterMap.end())
	{
		return characterMap[index];
	}
	else
	{
		//otherwise get the attributes from freetype
		int glyph_index = FT_Get_Char_Index(faceMap[this], index);
		auto error = FT_Load_Glyph(faceMap[this], glyph_index, FT_LOAD_DEFAULT);
		if (error)
		{
			std::cerr << "Failed to load " << index << "\n";
		}
		error = FT_Render_Glyph(faceMap[this]->glyph, FT_RENDER_MODE_NORMAL);
		if (error)
		{
			std::cerr << "Failed to render " << index << "\n";
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			faceMap[this]->glyph->bitmap.width,
			faceMap[this]->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			faceMap[this]->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Character character = {
			texture,
			faceMap[this]->glyph->bitmap.width,
			faceMap[this]->glyph->bitmap.rows,
			faceMap[this]->glyph->bitmap_left,
			faceMap[this]->glyph->bitmap_top,
			faceMap[this]->glyph->advance.x,
			faceMap[this]->glyph->advance.y};
		characterMap[index] = character;
		return characterMap[index];
	}
}

Font::~Font()
{
	hb_font_destroy((hb_font_t *)hbFont);
	FT_Done_Face(faceMap[this]);
	faceMap[this] = NULL;
}

u32string Font::FormatText(u32string input)
{
	hb_buffer_t *buf = hb_buffer_create();
	hb_buffer_add_utf32(buf, (const uint32_t *)input.c_str(), input.length(), 0, input.length());
	hb_buffer_set_direction(buf, HB_DIRECTION_LTR);
	hb_buffer_set_script(buf, HB_SCRIPT_LATIN);
	hb_buffer_set_language(buf, hb_language_from_string("en", -1));
	hb_shape((hb_font_t *)hbFont, buf, NULL, 0);
	unsigned int glyphCount;
	hb_glyph_info_t *glyph_info = hb_buffer_get_glyph_infos(buf, &glyphCount);
	hb_glyph_position_t *glyph_pos = hb_buffer_get_glyph_positions(buf, &glyphCount);
	for (int i = 0; i < glyphCount; ++i)
	{
		char32_t glyphid = glyph_info[i].codepoint;
		float x_offset = glyph_pos[i].x_offset / 64.0;
		float y_offset = glyph_pos[i].y_offset / 64.0;
		float x_advance = glyph_pos[i].x_advance / 64.0;
		float y_advance = glyph_pos[i].y_advance / 64.0;
	}
	hb_buffer_destroy(buf);
	return input;
}
} // namespace OpenXaml
