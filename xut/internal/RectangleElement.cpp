#include "internal/RectangleElement.h"

using namespace std;
using namespace xercesc;
RectangleElement::RectangleElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::Rectangle)
{
	init += "OpenXaml::Rectangle* %name%;\n";
	term += "delete %name%;\n";
	bodyInit += "%name% = new OpenXaml::Rectangle();\n";
	DOMAttr* fill = element->getAttributeNode(XMLString::transcode("Fill"));
	if (fill != NULL)
	{
		body += GetFill(fill, root);
	}
}