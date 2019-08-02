#pragma once
#include <string>
#include <vector>
#include <xercesc/dom/DOMElement.hpp>

class XamlElement 
{
public:
	std::vector<XamlElement*> Children;
	std::string Name = "";
	XamlElement(xercesc::DOMElement* element, bool root = false);
	~XamlElement();
	bool Public = false;
	std::string Initializer;
	std::string Body;
	std::string Terminator;
	std::string ChildEnumerator;
	std::string ExternalFunctions;
private:
	void GetFrameContent(xercesc::DOMElement* element);
	void GetButtonContent(xercesc::DOMElement* element);
	void GetRectangleContent(xercesc::DOMElement* element);
	void GetTextBlockContent(xercesc::DOMElement* element);
	void SetContent(std::string init, std::string body, std::string term, std::string name, std::string ext = "");
	void GetGridContent(xercesc::DOMElement* element);
	void GetGridRowDefinitions(xercesc::DOMElement* element);
	void GetGridColumnDefinitions(xercesc::DOMElement* element);
	void GetGridRowDefinition(xercesc::DOMElement* element);
	void GetGridColumnDefinition(xercesc::DOMElement* element);
	bool Root = false;
};

std::string GetFill(std::string input, bool root = false);
std::string GetHeight(std::string input, bool root = false);
std::string GetWidth(std::string input, bool root = false);
std::string GetHorizontalAlignment(std::string input);
std::string GetVerticalAlignment(std::string input);
std::string GetContent(std::string input);
std::string GetTextWrapping(std::string input);
std::string GetTextAlignment(std::string input);
std::string GetFontFamily(std::string input);
std::string GetFontSize(std::string input);
std::string GetText(std::string input);
std::string GetClickSigniture(std::string input);
std::string GetClickCall(std::string input);
