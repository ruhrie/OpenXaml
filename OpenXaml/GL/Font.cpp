#include "OpenXaml/GL/Font.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "OpenXaml/Environment.h"
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

std::map<Font*, FT_Face> faceMap;

namespace OpenXaml
{
	namespace Environment
	{
		extern FT_Library fontLibrary;
	}
}

Font::Font()
{

}

Font::Font(string file, float size)
{
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
}
Character& Font::operator[](const char index)
{
	if (characterMap.find(index) != characterMap.end())
	{
		return characterMap[index];
	}
	else
	{
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
			faceMap[this]->glyph->bitmap.buffer
		);
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
			faceMap[this]->glyph->advance.y
		};
		characterMap[index] = character;
		return characterMap[index];
	}
}

Font::~Font()
{
	FT_Done_Face(faceMap[this]);
	faceMap[this] = NULL;
}

