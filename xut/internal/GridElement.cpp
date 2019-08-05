#include "internal/GridElement.h"

using namespace std;
using namespace xercesc;
GridElement::GridElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::Grid)
{
	init += "OpenXaml::Grid* %name%;\n";
	term += "delete %name%;\n";
	bodyInit += "%name% = new OpenXaml::Grid();\n";
}