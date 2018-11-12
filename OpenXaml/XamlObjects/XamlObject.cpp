#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Frame.h"
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
	
}