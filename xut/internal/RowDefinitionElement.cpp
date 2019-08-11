#include "internal/RowDefinitionElement.h"

using namespace std;
using namespace xercesc;

namespace xut
{
	namespace elements
	{
		RowDefinitionElement::RowDefinitionElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::RowDefinition)
		{
			init += "OpenXaml::Objects::RowDefinition* %name%;\n";
			term += "delete %name%;\n";
			bodyInit += "%name% = new OpenXaml::Objects::RowDefinition();\n";
			/*DOMAttr* height = element->getAttributeNode(XMLString::transcode("Height"));
			if (height != NULL)
			{
				body += GetHeight(height, root);
			}*/
		}
	}
}