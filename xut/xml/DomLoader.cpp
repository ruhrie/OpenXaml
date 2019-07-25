#include "xml/DomLoader.h"
#include "xml/UID.h"
#include <sstream>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc\util\XMLString.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
using namespace xercesc;
using namespace OpenXaml;

XamlObject* LoadXaml(DOMElement* element)
{
	const XMLCh* xmlString = element->getTagName();
	string name = XMLString::transcode(xmlString);
	XamlObject* result;
	if (name == "Frame")
	{
		result = DomToFrame(element);
	}
	else if (name == "Button")
	{
		result = DomToButton(element);
	}
	else if (name == "Rectangle")
	{
		result = DomToRectangle(element);
	}
	else if (name == "TextBlock")
	{
		result = DomToTextBlock(element);
	}
	else
	{
		throw 2;
	}
}

Frame* DomToFrame(DOMElement* element)
{
	Frame* result = new Frame();
	DOMNamedNodeMap* attributes = element->getAttributes();
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string name = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);
		if (name == "Fill")
		{
			std::istringstream iss(value.substr(1, value.size()));
			unsigned int val;
			iss >> std::hex >> val;
			result->setFill(val);
		}
		else if (name == "Height")
		{
			result->setHeight(stoi(value));
		}
		else if (name == "Width")
		{
			result->setWidth(stoi(value));
		}
	}
	size_t childCount = element->getChildElementCount();
	auto children = element->getChildNodes();
	for (int i = 0; i < childCount; i++)
	{
		auto child = children->item(i);
		result->Children.push_back(LoadXaml((DOMElement*)child));
	}
	return result;
}

Button* DomToButton(DOMElement* element)
{
	Button* result = new Button();

	DOMNamedNodeMap* attributes = element->getAttributes();
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string name = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);
		if (name == "Height")
		{
			result->setHeight(stoi(value));
		}
		else if (name == "Width")
		{
			result->setWidth(stoi(value));
		}
		else if (name == "HorizontalAlignment")
		{
			if (value == "Right")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Right);
			}
			else if (value == "Left")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Left);
			}
			else if (value == "Center")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Center);
			}
			else if (value == "Stretch")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Stretch);
			}
		}
		else if (name == "VerticalAlignment")
		{
			if (value == "Top")
			{
				result->setVerticalAlignment(VerticalAlignment::Top);
			}
			else if (value == "Bottom")
			{
				result->setVerticalAlignment(VerticalAlignment::Bottom);
			}
			else if (value == "Center")
			{
				result->setVerticalAlignment(VerticalAlignment::Center);
			}
			else if (value == "Stretch")
			{
				result->setVerticalAlignment(VerticalAlignment::Stretch);
			}
		}
		else if (name == "Fill")
		{
			std::istringstream iss(value.substr(1, value.size()));
			unsigned int fill;
			iss >> std::hex >> fill;
			result->setFill(fill);
		}
		else if (name == "Content")
		{
			result->setContent(value);
		}
	}

	auto text = element->getTextContent();
	result->setContent(XMLString::transcode(text));
	size_t childCount = element->getChildElementCount();
	auto children = element->getChildNodes();
	for (int i = 0; i < childCount; i++)
	{
		auto child = children->item(i);
		result->Children.push_back(LoadXaml((DOMElement*)child));
	}
	return result;
}

OpenXaml::Rectangle* DomToRectangle(DOMElement* element)
{
	OpenXaml::Rectangle* result = new OpenXaml::Rectangle();

	DOMNamedNodeMap* attributes = element->getAttributes();
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string name = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);
		if (name == "Fill")
		{
			std::istringstream iss(value.substr(1, value.size()));
			unsigned int fill;
			iss >> std::hex >> fill;
			result->setFill(fill);
		}
		else if (name == "Height")
		{
			result->setHeight(stoi(value));
		}
		else if (name == "Width")
		{
			result->setWidth(stoi(value));
		}
		else if (name == "HorizontalAlignment")
		{
			if (value == "Right")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Right);
			}
			else if (value == "Left")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Left);
			}
			else if (value == "Center")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Center);
			}
			else if (value == "Stretch")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Stretch);
			}
		}
		else if (name == "VerticalAlignment")
		{
			if (value == "Top")
			{
				result->setVerticalAlignment(VerticalAlignment::Top);
			}
			else if (value == "Bottom")
			{
				result->setVerticalAlignment(VerticalAlignment::Bottom);
			}
			else if (value == "Center")
			{
				result->setVerticalAlignment(VerticalAlignment::Center);
			}
			else if (value == "Stretch")
			{
				result->setVerticalAlignment(VerticalAlignment::Stretch);
			}
		}
	}

	size_t childCount = element->getChildElementCount();
	auto children = element->getChildNodes();
	for (int i = 0; i < childCount; i++)
	{
		auto child = children->item(i);
		result->Children.push_back(LoadXaml((DOMElement*)child));
	}
	return result;
}

OpenXaml::TextBlock* DomToTextBlock(xercesc::DOMElement* element)
{
	TextBlock* result = new TextBlock();

	DOMNamedNodeMap* attributes = element->getAttributes();
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string name = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);

		if (name == "Height")
		{
			result->setHeight(stoi(value));
		}
		else if (name == "Width")
		{
			result->setWidth(stoi(value));
		}
		else if (name == "HorizontalAlignment")
		{
			if (value == "Right")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Right);
			}
			else if (value == "Left")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Left);
			}
			else if (value == "Center")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Center);
			}
			else if (value == "Stretch")
			{
				result->setHorizontalAlignment(HorizontalAlignment::Stretch);
			}
		}
		else if (name == "VerticalAlignment")
		{
			if (value == "Top")
			{
				result->setVerticalAlignment(VerticalAlignment::Top);
			}
			else if (value == "Bottom")
			{
				result->setVerticalAlignment(VerticalAlignment::Bottom);
			}
			else if (value == "Center")
			{
				result->setVerticalAlignment(VerticalAlignment::Center);
			}
			else if (value == "Stretch")
			{
				result->setVerticalAlignment(VerticalAlignment::Stretch);
			}
		}
		else if (name == "TextWrapping")
		{
			if (value == "None")
			{
				result->setTextWrapping(TextWrapping::None);
			}
			else if (value == "Wrap")
			{
				result->setTextWrapping(TextWrapping::Wrap);
			}
		}
		else if (name == "FontFamily")
		{
			result->setFontFamily(value);
		}
		else if (name == "FontSize")
		{
			result->setFontSize(stof(value));
		}
		else if (name == "Fill")
		{
			std::istringstream iss(value.substr(1, value.size()));
			unsigned int fill;
			iss >> std::hex >> fill;
			result->setFill(fill);
		}
		else if (name == "TextAlignment")
		{
			if (value == "Left")
			{
				result->setTextAlignment(TextAlignment::Left);
			}
			else if (value == "Right")
			{
				result->setTextAlignment(TextAlignment::Right);
			}
			else if (value == "Center")
			{
				result->setTextAlignment(TextAlignment::Center);
			}
		}
	}

	auto text = element->getTextContent();
	result->setText(XMLString::transcode(text));

	size_t childCount = element->getChildElementCount();
	auto children = element->getChildNodes();
	for (int i = 0; i < childCount; i++)
	{
		auto child = children->item(i);
		result->Children.push_back(LoadXaml((DOMElement*)child));
	}

	return result;
}

void XamlToString(std::string& result, xercesc::DOMElement* element)
{
	const XMLCh* xmlString = element->getTagName();
	string name = XMLString::transcode(xmlString);
	if (name == "Frame")
	{
		result += StringFromFrame(element);
	}
	else if (name == "Button")
	{
		result += StringFromButton(element);
	}
	else if (name == "Rectangle")
	{
		result += StringFromRectangle(element);
	}
	else if (name == "TextBlock")
	{
		result += StringFromTextBlock(element);
	}
	else
	{
		throw 2;
	}

}

std::string StringFromFrame(xercesc::DOMElement* element)
{
	string result = "";

	string nameToBe = "";

	string postInit = "";

	result += "OpenXaml::Frame %name% = new OpenXaml::Frame();\n";

	DOMNamedNodeMap* attributes = element->getAttributes();
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string name = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);
		if (name == "Fill")
		{
			std::istringstream iss(value.substr(1, value.size()));
			unsigned int val;
			iss >> std::hex >> val;
			result += "%name%->setFill(" + to_string(val) + ");\n";
		}
		else if (name == "Height")
		{
			result += "%name%->setHeight(" + to_string(stoi(value)) + ");\n";
		}
		else if (name == "Width")
		{
			result += "%name%->setWidth(" + to_string(stoi(value)) + ");\n";
		}
	}
	
	if (nameToBe == "")
	{
		nameToBe = "var_" + to_string(GetUID());
	}
	size_t pos = 0;
	while ((pos = result.find("%name%", 0)) != std::string::npos)
	{
		result.replace(pos, 6, nameToBe);
	}

	return result;
}
std::string StringFromButton(xercesc::DOMElement* element)
{
	string result = "button";
	return result;
}
std::string StringFromRectangle(xercesc::DOMElement* element)
{
	string result = "rectangle";
	return result;
}
std::string StringFromTextBlock(xercesc::DOMElement* element)
{
	string result = "textblock";
	return result;
}