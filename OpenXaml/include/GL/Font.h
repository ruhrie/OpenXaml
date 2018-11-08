#ifndef Font_h
#define Font_h
#include <string>
#include <map>
#include <ft2build.h>
#include "GL/Character.h"
#include FT_FREETYPE_H
using namespace std;
class Font
{
public:
	Font(FT_Library lib, string file);
private:
	FT_Face face;
	map<char, Character> characterMap;
};

#endif