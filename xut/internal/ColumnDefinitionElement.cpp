#include "internal/ColumnDefinitionElement.h"

using namespace std;
using namespace xercesc;
namespace xut
{
	namespace elements
	{
		ColumnDefinitionElement::ColumnDefinitionElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::ColumnDefinition)
		{
			init += "OpenXaml::Objects::ColumnDefinition* %name%;\n";
			//term += "delete %name%;\n";
			bodyInit += "%name% = new OpenXaml::Objects::ColumnDefinition();\n";
			/*DOMAttr* width = element->getAttributeNode(XMLString::transcode("Width"));
			if (width != NULL)
			{
				body += GetWidth(width, root);
			}*/
		}
	}
}