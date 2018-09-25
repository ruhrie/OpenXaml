#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Frame.h"
#include <glad/glad.h>

Frame::Frame()
{

}

void Frame::Draw(float xmin, float xmax, float ymin, float ymax)
{
	for (unsigned int i = 0; i < Children.size(); i++)
	{
		Children[i]->Draw(xmin, xmax, ymin, ymax);
	}
}

void Frame::Draw()
{
	Frame::Draw(-1.0f, 1.0f, -1.0f, 1.0f);
}

void Frame::Initialize()
{
	for (unsigned int i = 0; i < Children.size(); i++)
	{
		Children[i]->Initialize();
	}
}