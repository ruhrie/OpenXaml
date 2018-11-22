#ifndef Character_h
#define Character_h
#include <glad/glad.h>
struct Character
{
	GLuint TextureID;
	int Width;
	int Height;
	int BearingX;
	int BearingY;
	int AdvanceX;
	int AdvanceY;
};

#endif