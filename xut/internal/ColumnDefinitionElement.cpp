#include "internal/ColumnDefinitionElement.h"

using namespace std;
using namespace xercesc;
ColumnDefinitionElement::ColumnDefinitionElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::ColumnDefinition)
{
	init += "OpenXaml::ColumnDefinition* %name%;\n";
	term += "delete %name%;\n";
	bodyInit += "%name% = new OpenXaml::ColumnDefinition();\n";
	/*DOMAttr* width = element->getAttributeNode(XMLString::transcode("Width"));
	if (width != NULL)
	{
		body += GetWidth(width, root);
	}*/
}