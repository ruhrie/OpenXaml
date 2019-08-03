#include "internal/XamlElement.h"
#include "xml/UID.h"
#include <sstream>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <iostream>
using namespace std;
using namespace xercesc;

std::string FormatString(std::string input)
{
	std::string result = "";
	for (auto ch : input)
	{
		switch (ch)
		{
		case '\'':
			result += "\\'";
			break;

		case '\"':
			result += "\\\"";
			break;

		case '\?':
			result += "\\?";
			break;

		case '\\':
			result += "\\\\";
			break;

		case '\a':
			result += "\\a";
			break;

		case '\b':
			result += "\\b";
			break;

		case '\f':
			result += "\\f";
			break;

		case '\n':
			result += "\\n";
			break;

		case '\r':
			result += "\\r";
			break;

		case '\t':
			result += "\\t";
			break;

		case '\v':
			result += "\\v";
			break;

		default:
			result += ch;
		}
	}
	return result;
}

XamlElement::XamlElement(xercesc::DOMElement* element, bool root)
{
	Root = root;
	const XMLCh* xmlString = element->getTagName();
	string name = xercesc::XMLString::transcode(xmlString);
	if (name == "Frame")
	{
		GetFrameContent(element);
	}
	else if (name == "Button")
	{
		GetButtonContent(element);
	}
	else if (name == "Rectangle")
	{
		GetRectangleContent(element);
	}
	else if (name == "TextBlock")
	{
		GetTextBlockContent(element);
	}
	else if (name == "Grid")
	{
		GetGridContent(element);
	}
	else if (name == "RowDefinition")
	{
		GetGridRowDefinition(element);
	}
	else if (name == "ColumnDefinition")
	{
		GetGridColumnDefinition(element);
	}
	else if (name == "RowDefinitionCollection")
	{

	}
	else if (name == "ColumnDefinitionCollection")
	{

	}
	size_t childCount = element->getChildElementCount();
	auto children = element->getChildNodes();
	for (int i = 0; i < childCount; i++)
	{
		auto child = children->item(i);
		XamlElement* childElement = new XamlElement((DOMElement*)child);
		if (root)
		{
			ChildEnumerator += "Children.push_back(" + childElement->Name + ");\n";
		}
		else
		{
			ChildEnumerator += Name + "->Children.push_back(" + childElement->Name + ");\n";
		}

		Children.push_back(childElement);
	}
}

void XamlElement::GetFrameContent(DOMElement* element)
{
	Type = ElementType::Frame;
	string init = "";
	string term = "";
	string body = "";
	string name = "";
	if (!Root)
	{
		init += "OpenXaml::Frame* %name%;\n";
		term += "delete %name%;\n";
		body += "%name% = new OpenXaml::Frame();\n";
	}

	DOMNamedNodeMap* attributes = element->getAttributes();
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string propertyName = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);
		if (propertyName == "Fill")
		{
			body += GetFill(value, Root);
		}
		else if (propertyName == "Height")
		{
			body += GetHeight(value, Root);
		}
		else if (propertyName == "Width")
		{
			body += GetWidth(value, Root);
		}
	}

	SetContent(init, body, term, name);
}

void XamlElement::SetContent(std::string init, std::string body, std::string term, std::string name, std::string ext)
{
	if (name == "")
	{
		name = "var_" + to_string(GetUID());
	}
	else
	{
		Public = true;
	}
	size_t pos = 0;
	while ((pos = init.find("%name%", 0)) != std::string::npos)
	{
		init.replace(pos, 6, name);
	}
	while ((pos = body.find("%name%", 0)) != std::string::npos)
	{
		body.replace(pos, 6, name);
	}
	while ((pos = term.find("%name%", 0)) != std::string::npos)
	{
		term.replace(pos, 6, name);
	}
	Initializer = init;
	Body = body;
	Terminator = term;
	Name = name;
	ExternalFunctions = ext;
}

std::string GetFill(string input, bool root)
{
	std::istringstream iss(input.substr(1, input.size()));
	unsigned int val;
	iss >> std::hex >> val;
	string result = "";
	if (root)
	{
		result += "setFill(" + to_string(val) + ");\n";
	}
	else
	{
		result += "%name%->setFill(" + to_string(val) + ");\n";
	}
	return result;
}

string GetHeight(string input, bool root)
{
	if (root)
	{
		return "setHeight(" + to_string(stoi(input)) + ");\n";
	}
	else
	{
		return "%name%->setHeight(" + to_string(stoi(input)) + ");\n";
	}

}

string GetWidth(string input, bool root)
{
	if (root)
	{
		return "setWidth(" + to_string(stoi(input)) + ");\n";
	}
	else
	{
		return "%name%->setWidth(" + to_string(stoi(input)) + ");\n";
	}
}

string GetHorizontalAlignment(string input)
{
	if (input == "Right")
	{
		return "%name%->setHorizontalAlignment(OpenXaml::HorizontalAlignment::Right);\n";
	}
	else if (input == "Left")
	{
		return "%name%->setHorizontalAlignment(OpenXaml::HorizontalAlignment::Left);\n";
	}
	else if (input == "Center")
	{
		return "%name%->setHorizontalAlignment(OpenXaml::HorizontalAlignment::Center);\n";
	}
	else if (input == "Stretch")
	{
		return "%name%->setHorizontalAlignment(OpenXaml::HorizontalAlignment::Stretch);\n";
	}
	else
	{
		throw 2;
	}
}

string GetVerticalAlignment(string input)
{
	if (input == "Top")
	{
		return "%name%->setVerticalAlignment(OpenXaml::VerticalAlignment::Top);\n";
	}
	else if (input == "Bottom")
	{
		return "%name%->setVerticalAlignment(OpenXaml::VerticalAlignment::Bottom);\n";
	}
	else if (input == "Center")
	{
		return "%name%->setVerticalAlignment(OpenXaml::VerticalAlignment::Center);\n";
	}
	else if (input == "Stretch")
	{
		return "%name%->setVerticalAlignment(OpenXaml::VerticalAlignment::Stretch);\n";
	}
	else
	{
		throw 2;
	}
}

void XamlElement::GetButtonContent(xercesc::DOMElement* element)
{
	Type = ElementType::Button;
	string init = "OpenXaml::Button* %name%;\n";
	string term = "delete %name%;\n";
	string body = "";
	string name = "";
	string ext = "";
	body += "%name% = new OpenXaml::Button();\n";
	DOMNamedNodeMap* attributes = element->getAttributes();
	bool contentDone = false;
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string propertyName = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);
		if (propertyName == "Height")
		{
			body += GetHeight(value);
		}
		else if (propertyName == "Width")
		{
			body += GetWidth(value);
		}
		else if (propertyName == "HorizontalAlignment")
		{
			body += GetHorizontalAlignment(value);
		}
		else if (propertyName == "VerticalAlignment")
		{
			body += GetVerticalAlignment(value);
		}
		else if (propertyName == "Fill")
		{
			body += GetFill(value);
		}
		else if (propertyName == "Content")
		{
			body += GetContent(value);
			contentDone = true;
		}
		else if (propertyName == "OnClick")
		{
			ext += GetClickSigniture(value);
			body += GetClickCall(value);
		}
	}

	auto text = element->getTextContent();
	if (!contentDone)
	{
		body += GetContent(XMLString::transcode(text));
	}

	SetContent(init, body, term, name, ext);
}

string GetContent(string input)
{
	return "%name%->setContent(\"" + input + "\");\n";
}

void XamlElement::GetRectangleContent(xercesc::DOMElement* element)
{
	Type = ElementType::Rectangle;
	string init = "OpenXaml::Rectangle* %name%;\n";
	string term = "delete %name%;\n";
	string body = "";
	string name = "";
	body += "%name% = new OpenXaml::Rectangle();\n";
	DOMNamedNodeMap* attributes = element->getAttributes();
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string propertyName = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);
		if (propertyName == "Fill")
		{
			body += GetFill(value);
		}
		else if (propertyName == "Height")
		{
			body += GetHeight(value);
		}
		else if (propertyName == "Width")
		{
			body += GetWidth(value);
		}
		else if (propertyName == "HorizontalAlignment")
		{
			body += GetHorizontalAlignment(value);
		}
		else if (propertyName == "VerticalAlignment")
		{
			body += GetVerticalAlignment(value);
		}
	}

	SetContent(init, body, term, name);
}

void XamlElement::GetTextBlockContent(xercesc::DOMElement* element)
{
	Type = ElementType::TextBlock;
	string init = "OpenXaml::TextBlock* %name%;\n";
	string term = "delete %name%;\n";
	string body = "";
	string name = "";
	body += "%name% = new OpenXaml::TextBlock();\n";
	DOMNamedNodeMap* attributes = element->getAttributes();
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string propertyName = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);

		if (propertyName == "Height")
		{
			body += GetHeight(value);
		}
		else if (propertyName == "Width")
		{
			body += GetWidth(value);
		}
		else if (propertyName == "HorizontalAlignment")
		{
			body += GetHorizontalAlignment(value);
		}
		else if (propertyName == "VerticalAlignment")
		{
			body += GetVerticalAlignment(value);
		}
		else if (propertyName == "TextWrapping")
		{
			body += GetTextWrapping(value);
		}
		else if (propertyName == "FontFamily")
		{
			body += GetFontFamily(value);
		}
		else if (propertyName == "FontSize")
		{
			body += GetFontSize(value);
		}
		else if (propertyName == "Fill")
		{
			body += GetFill(value);
		}
		else if (propertyName == "TextAlignment")
		{
			body += GetTextAlignment(value);
		}
	}

	auto text = element->getTextContent();
	body += GetText("\"" + FormatString(XMLString::transcode(text)) + "\"");

	SetContent(init, body, term, name);
}

std::string GetFontFamily(std::string input)
{
	return "%name%->setFontFamily(" + input + ");\n";
}
std::string GetFontSize(std::string input)
{
	return "%name%->setFontSize(" + to_string(stof(input)) + ");\n";
}

std::string GetTextAlignment(std::string input)
{
	if (input == "Left")
	{
		return "%name%->setTextAlignment(TextAlignment::Left);\n";
	}
	else if (input == "Right")
	{
		return "%name%->setTextAlignment(TextAlignment::Right);\n";
	}
	else if (input == "Center")
	{
		return "%name%->setTextAlignment(TextAlignment::Center);\n";
	}
	else
	{
		throw 2;
	}
}

std::string GetText(std::string input)
{
	return "%name%->setText(" + input + ");\n";
}

std::string GetTextWrapping(std::string input)
{
	if (input == "None")
	{
		return "%name%->setTextWrapping(OpenXaml::TextWrapping::None);\n";
	}
	else if (input == "Wrap")
	{
		return "%name%->setTextWrapping(OpenXaml::TextWrapping::Wrap);\n";
	}
	else if (input == "WrapWholeWords")
	{
		return "%name%->setTextWrapping(OpenXaml::TextWrapping::WrapWholeWords);\n";
	}
	else
	{
		throw 2;
	}
}

XamlElement::~XamlElement()
{
	for (XamlElement* element : Children)
	{
		delete element;
	}
}

std::string GetClickSigniture(std::string input)
{
	std::string result = "";
	result += "virtual void " + input + "(OpenXaml::XamlObject* sender) = 0;\n";
	return result;
}

std::string GetClickCall(std::string input)
{
	std::string result = "";
	result += "%name%->setOnClick(std::bind(&%master%::" + input + ", this, %name%));\n";
	return result;
}

void XamlElement::GetGridContent(xercesc::DOMElement* element)
{
	Type = ElementType::Grid;
	string init = "OpenXaml::Grid* %name%;\n";
	string term = "delete %name%;\n";
	string body = "";
	string name = "";
	body += "%name% = new OpenXaml::Grid();\n";
	DOMNamedNodeMap* attributes = element->getAttributes();
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string propertyName = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);
	}

	SetContent(init, body, term, name);
}
void XamlElement::GetGridRowDefinition(xercesc::DOMElement* element)
{
	Type = ElementType::RowDefinition;
	string init = "OpenXaml::RowDefinition* %name%;\n";
	string term = "delete %name%;\n";
	string body = "";
	string name = "";
	body += "%name% = new OpenXaml::RowDefinition();\n";
	DOMNamedNodeMap* attributes = element->getAttributes();
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string propertyName = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);
	}
	SetContent(init, body, term, name);
}
void XamlElement::GetGridColumnDefinition(xercesc::DOMElement* element)
{
	Type = ElementType::ColumnDefinition;
	string init = "OpenXaml::ColumnDefinition* %name%;\n";
	string term = "delete %name%;\n";
	string body = "";
	string name = "";
	body += "%name% = new OpenXaml::ColumnDefinition();\n";
	DOMNamedNodeMap* attributes = element->getAttributes();
	for (int i = 0; i < attributes->getLength(); i++)
	{
		DOMNode* item = attributes->item(i);
		const XMLCh* nameXML = item->getNodeName();
		const XMLCh* valXML = item->getNodeValue();
		string propertyName = XMLString::transcode(nameXML);
		string value = XMLString::transcode(valXML);
	}
	SetContent(init, body, term, name);
}