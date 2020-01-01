#include "internal/ButtonElement.h"

using namespace std;
using namespace xercesc;
namespace xut
{
	namespace elements
	{
		ButtonElement::ButtonElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::Button)
		{
			init += "std::shared_ptr<OpenXaml::Objects::Button> %name%;\n";
			bodyInit += "%name% = std::make_shared<OpenXaml::Objects::Button>();\n";
			DOMAttr* fill = element->getAttributeNode(XMLString::transcode("Fill"));
			if (fill != NULL)
			{
				body += GetFill(fill, root);
			}
			DOMAttr* content = element->getAttributeNode(XMLString::transcode("Text"));
			if (content != NULL)
			{
				body += GetText(content);
			}
			else
			{
				body += GetText(XMLString::transcode(element->getTextContent()));
			}
		}
	}
}