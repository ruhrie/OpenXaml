#include "XamlObjects/XamlObject.h"

void XamlObject::SetScale(float scale, bool isHorizontal)
{
	if (isHorizontal)
	{
		XamlObject::xScale = scale;
	}
	else
	{
		XamlObject::yScale = scale;
	}
	for (int i = 0; i < Children.size(); i++)
	{
		Children[i]->SetScale(scale, isHorizontal);
	}
}

float XamlObject::GetScale(bool horizontal)
{
	if (horizontal)
	{
		return xScale;
	}
	else
	{
		return yScale;
	}
}