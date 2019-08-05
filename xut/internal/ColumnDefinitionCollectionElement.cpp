#include "internal/ColumnDefinitionCollectionElement.h"

using namespace std;
using namespace xercesc;
ColumnDefinitionCollectionElement::ColumnDefinitionCollectionElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::ColumnDefinitionCollection)
{
	init += "OpenXaml::ColumnDefinitionCollection* %name%;\n";
	term += "delete %name%;\n";
	bodyInit += "%name% = new OpenXaml::ColumnDefinitionCollection();\n";
}