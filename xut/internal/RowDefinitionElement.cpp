#include "internal/RowDefinitionElement.h"

using namespace std;
using namespace xercesc;

namespace xut
{
	namespace elements
	{
		RowDefinitionElement::RowDefinitionElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::RowDefinition)
		{
			init += "std::shared_ptr<OpenXaml::Objects::RowDefinition> %name%;\n";
			bodyInit += "%name% = std::make_shared<OpenXaml::Objects::RowDefinition>();\n";
		}
	}
}