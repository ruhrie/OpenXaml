#include "internal/XamlElement.h"
#include <string>
#include <map>
class XamlClass
{
public:
	std::map<std::string, XamlElement*> Interfaces;
	std::string ToString();
};