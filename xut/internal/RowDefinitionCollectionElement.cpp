#include "internal/RowDefinitionCollectionElement.h"

using namespace std;
using namespace xercesc;

namespace xut
{
	namespace elements
	{
		RowDefinitionCollectionElement::RowDefinitionCollectionElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::RowDefinitionCollection)
		{
			init += "OpenXaml::Objects::RowDefinitionCollection* %name%;\n";
			term += "delete %name%;\n";
			bodyInit += "%name% = new OpenXaml::Objects::RowDefinitionCollection();\n";
		}
	}
}