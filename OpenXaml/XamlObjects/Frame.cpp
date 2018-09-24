#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Frame.h"

Frame::Frame()
{
}

void Frame::Draw()
{
	for (int i = 0; i < Children.size(); i++)
	{
		Children[i]->Draw();
	}
}