#pragma once
#include <string>
#include <vector>
#include <xercesc/dom/DOMElement.hpp>

class XamlElement 
{
public:
	std::vector<XamlElement*> Children;
	std::string Name = "";
	XamlElement(xercesc::DOMElement* element);
	~XamlElement();
private:
	bool Public = false;
	std::string Initializer = "";
	std::string Body;
	std::string Terminator;
	void GetFrameContent(xercesc::DOMElement* element);
	void GetButtonContent(xercesc::DOMElement* element);
	void GetRectangleContent(xercesc::DOMElement* element);
	void GetTextBlockContent(xercesc::DOMElement* element);
	void SetContent(std::string init, std::string body, std::string term, std::string name);
};

std::string GetFill(std::string input);
std::string GetHeight(std::string input);
std::string GetWidth(std::string input);
std::string GetHorizontalAlignment(std::string input);
std::string GetVerticalAlignment(std::string input);
std::string GetContent(std::string input);
std::string GetTextWrapping(std::string input);
std::string GetTextAlignment(std::string input);
std::string GetFontFamily(std::string input);
std::string GetFontSize(std::string input);
std::string GetText(std::string input);
