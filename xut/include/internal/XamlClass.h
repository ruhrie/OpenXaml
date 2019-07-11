#pragma once
#include "internal/XamlElement.h"
#include <string>
#include <map>
class XamlClass
{
public:
	std::string Name;
	std::string PublicInterfaces = "";
	std::string PrivateInterfaces = "";
	std::string Initializer = "";
	std::string Terminator = "";
	std::string ToString();
	XamlClass(std::string name, XamlElement* element);
	void WriteToFile(std::string fileName);
private:
	void AddXamlElement(XamlElement* element);
};