#ifndef Character_h
#define Character_h
#include <glad/glad.h>
struct Character
{
	GLuint TextureID;
	unsigned int Width;
	unsigned int Height;
	int BearingX;
	int BearingY;
	int AdvanceX;
	int AdvanceY;
};

#endif