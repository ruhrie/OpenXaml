#include "internal/ColumnDefinitionCollectionElement.h"

using namespace std;
using namespace xercesc;
namespace xut
{
	namespace elements
	{
		ColumnDefinitionCollectionElement::ColumnDefinitionCollectionElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::ColumnDefinitionCollection)
		{
			init += "std::shared_ptr<OpenXaml::Objects::ColumnDefinitionCollection> %name%;\n";
			bodyInit += "%name% = std::make_shared<OpenXaml::Objects::ColumnDefinitionCollection>();\n";
		}
	}
}