#include <glad/glad.h>
#pragma once
struct Character
{
	unsigned int TextureID;
	unsigned int Width;
	unsigned int Height;
	int BearingX;
	int BearingY;
	long AdvanceX;
	long AdvanceY;
};
