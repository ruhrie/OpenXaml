#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Frame.h"
#include "XamlObjects/Rectangle.h"
#include <iostream>

using namespace OpenXaml;

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

shared_ptr<XamlObject> XamlObject::ParseObject(DOMElement * obj)
{
	const XMLCh *xmlString = obj->getTagName();
	string name = XMLString::transcode(xmlString);
	shared_ptr<XamlObject> result;
	if (name == "Frame")
	{
		result = make_shared<OpenXaml::Frame>();
	}
	else
	{
		throw 2;
	}
	result->LoadFromDOM(obj);
	return result;
}

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
			//OpenXaml::Rectangle rect = OpenXaml::Rectangle();
			//rect.LoadFromDOM((DOMElement*) child);
			shared_ptr<OpenXaml::Rectangle> asdf = make_shared<OpenXaml::Rectangle>();
			asdf->LoadFromDOM((DOMElement*)child);
			Children.push_back(asdf);
		}
		else
		{
			std::cout << "Unrecognized type: " << type << "\n";
		}
		
	}
}