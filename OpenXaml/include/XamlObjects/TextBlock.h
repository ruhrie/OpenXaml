#ifndef FRAME_H
#define FRAME_H
#include "XamlObjects/XamlObject.h"
//https://learnopengl.com/In-Practice/Text-Rendering
class TextBlock : public XamlObject
{
	void Draw(float xmin, float xmax, float ymin, float ymax);
};

#endif