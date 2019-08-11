#include "internal/ColumnDefinitionCollectionElement.h"

using namespace std;
using namespace xercesc;
namespace xut
{
	namespace elements
	{
		ColumnDefinitionCollectionElement::ColumnDefinitionCollectionElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::ColumnDefinitionCollection)
		{
			init += "OpenXaml::Objects::ColumnDefinitionCollection* %name%;\n";
			term += "delete %name%;\n";
			bodyInit += "%name% = new OpenXaml::Objects::ColumnDefinitionCollection();\n";
		}
	}
}