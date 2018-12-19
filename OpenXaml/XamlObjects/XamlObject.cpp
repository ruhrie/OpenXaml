#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Rectangle.h"
#include "XamlObjects/TextBlock.h"
#include <iostream>

using namespace OpenXaml;

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
	HorizontalAlignment.onPropertyChanged = std::bind(&XamlObject::Update, this);
	VerticalAlignment.onPropertyChanged = std::bind(&XamlObject::Update, this);
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