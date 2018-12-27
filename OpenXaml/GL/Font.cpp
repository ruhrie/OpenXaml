#include "GL/Font.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "Environment.h"

Font::Font()
{

}

Font::Font(FT_Library lib, string file, float size)
{
	auto error = FT_New_Face(lib, file.c_str(), 0, &face);
	if (error)
	{
		std::cerr << "Failed to open " << file << "\n";
		return;
	}
	float dpi = OpenXaml::env.getDPI();
	FT_Set_Char_Size(face, 0, (int)(size * 64), (int)dpi, (int)dpi);
	Height = face->size->metrics.height;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}
Character& Font::operator[](const char index)
{
	if (characterMap.find(index) != characterMap.end())
	{
		return characterMap[index];
	}
	else
	{
		int glyph_index = FT_Get_Char_Index(face, index);
		auto error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		if (error)
		{
			std::cerr << "Failed to load " << index << "\n";
		}
		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
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
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Character character = {
			texture,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			face->glyph->bitmap_left,
			face->glyph->bitmap_top,
			face->glyph->advance.x,
			face->glyph->advance.y
		};
		characterMap[index] = character;
		return characterMap[index];
	}
}

Font::~Font()
{
	FT_Done_Face(face);
}

