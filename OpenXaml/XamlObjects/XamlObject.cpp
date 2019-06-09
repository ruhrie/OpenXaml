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
			shared_ptr<OpenXaml::Rectangle> res = make_shared<OpenXaml::Rectangle>();
			res->LoadFromDOM((DOMElement*)child);
			Children.push_back(res);
		}
		else if (type == "TextBlock")
		{
			shared_ptr<OpenXaml::TextBlock> res = make_shared<OpenXaml::TextBlock>();
			res->LoadFromDOM((DOMElement*)child);
			Children.push_back(res);
		}
		else if (type == "Button")
		{
			shared_ptr<OpenXaml::Button> res = make_shared<OpenXaml::Button>();
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

XamlObject::XamlObject()
{
	this->Height = 0;
	this->Width = 0;
	this->VAO = 0;
	this->PixelScale = coordinate{ 0,0 };
	this->minCoord = coordinate{ 0,0 };
	this->maxCoord = coordinate{ 0,0 };
	this->shaderProgram = 0;
}

void XamlObject::setPixelScale(float x, float y)
{
	PixelScale = coordinate{x,y};
	for (int i = 0; i < Children.size(); i++)
	{
		Children[i]->setPixelScale(PixelScale);
	}
	Update();
}
void XamlObject::setPixelScale(coordinate scale)
{
	PixelScale = scale;
	for (int i = 0; i < Children.size(); i++)
	{
		Children[i]->setPixelScale(PixelScale);
	}
	Update();
}

void XamlObject::setHorizontalAlignment(OpenXaml::HorizontalAlignment alignment)
{
	this->HorizontalAlignment = alignment;
	this->Update();
}

void XamlObject::setVerticalAlignment(OpenXaml::VerticalAlignment alignment)
{
	this->VerticalAlignment = alignment;
	this->Update();
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
	this->Update();
}
int XamlObject::getHeight()
{
	return this->Height;
}
void XamlObject::setWidth(int width)
{
	this->Width = width;
	this->Update();
}
int XamlObject::getWidth()
{
	return this->Width;
}