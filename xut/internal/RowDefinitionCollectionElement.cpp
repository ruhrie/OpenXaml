#include "internal/RowDefinitionCollectionElement.h"

using namespace std;
using namespace xercesc;
RowDefinitionCollectionElement::RowDefinitionCollectionElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::RowDefinitionCollection)
{
	init += "OpenXaml::RowDefinitionCollection* %name%;\n";
	term += "delete %name%;\n";
	bodyInit += "%name% = new OpenXaml::RowDefinitionCollection();\n";
}