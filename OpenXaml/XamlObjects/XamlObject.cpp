#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Rectangle.h"
#include "XamlObjects/TextBlock.h"
#include "XamlObjects/Button.h"
#include "Properties/Alignment.h"
#include <iostream>

using namespace OpenXaml;
using namespace std;

void XamlObject::LoadChildrenFromDOM(DOMElement *root)
{
	size_t childCount = root->getChildElementCount();
	auto children = root->getChildNodes();
	for (int i = 0; i < childCount; i++)
	{
		auto child = children->item(i);
		auto typeC = child->getNodeName();
		string type = XMLString::transcode(typeC);
		if (type == "Rectangle")
		{
			OpenXaml::Rectangle* res = new Rectangle();
			res->LoadFromDOM((DOMElement*)child);
			Children.push_back(res);
		}
		else if (type == "TextBlock")
		{
			OpenXaml::TextBlock* res = new TextBlock();
			res->LoadFromDOM((DOMElement*)child);
			Children.push_back(res);
		}
		else if (type == "Button")
		{
			OpenXaml::Button* res = new Button();
			res->LoadFromDOM((DOMElement*)child);
			Children.push_back(res);
		}
		else
		{
			std::cerr << "Unrecognized type: " << type << "\n";	
		}
		
	}
}

void XamlObject::SetBoundingBox(coordinate min, coordinate max)
{
	minCoord = min;
	maxCoord = max;
}

bool XamlObject::IsContained(coordinate input)
{
	if (input.x > minCoord.x && input.x < maxCoord.x)
	{
		if (input.y > minCoord.y && input.y < maxCoord.y)
		{
			return true;
		}
	}
	return false;
}

XamlObject::XamlObject()
{
	this->Height = 0;
	this->Width = 0;
	this->VAO = 0;
	this->PixelScale = coordinate{ 0,0 };
	this->minCoord = coordinate{ 0,0 };
	this->maxCoord = coordinate{ 0,0 };
}

void XamlObject::setPixelScale(float x, float y)
{
	PixelScale = coordinate{x,y};
	for (int i = 0; i < Children.size(); i++)
	{
		Children[i]->setPixelScale(PixelScale);
	}
}
void XamlObject::setPixelScale(coordinate scale)
{
	PixelScale = scale;
	for (int i = 0; i < Children.size(); i++)
	{
		Children[i]->setPixelScale(PixelScale);
	}
}

void XamlObject::setHorizontalAlignment(OpenXaml::HorizontalAlignment alignment)
{
	this->HorizontalAlignment = alignment;
}

void XamlObject::setVerticalAlignment(OpenXaml::VerticalAlignment alignment)
{
	this->VerticalAlignment = alignment;
}

HorizontalAlignment XamlObject::getHorizontalAlignment()
{
	return this->HorizontalAlignment;
}

VerticalAlignment XamlObject::getVerticalAlignment()
{
	return this->VerticalAlignment;
}

void XamlObject::setHeight(int height)
{
	this->Height = height;
}
int XamlObject::getHeight()
{
	return this->Height;
}
void XamlObject::setWidth(int width)
{
	this->Width = width;
}
int XamlObject::getWidth()
{
	return this->Width;
}