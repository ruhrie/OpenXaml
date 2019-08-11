#include "internal/ButtonElement.h"

using namespace std;
using namespace xercesc;
namespace xut
{
	namespace elements
	{
		ButtonElement::ButtonElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::Button)
		{
			init += "OpenXaml::Objects::Button* %name%;\n";
			term += "delete %name%;\n";
			bodyInit += "%name% = new OpenXaml::Objects::Button();\n";
			DOMAttr* fill = element->getAttributeNode(XMLString::transcode("Fill"));
			if (fill != NULL)
			{
				body += GetFill(fill, root);
			}
			DOMAttr* onClick = element->getAttributeNode(XMLString::transcode("OnClick"));
			if (onClick != NULL)
			{
				ext += GetClickSigniture(onClick);
				body += GetClickCall(onClick);
			}
			DOMAttr* content = element->getAttributeNode(XMLString::transcode("Content"));
			if (content != NULL)
			{
				body += GetContent(content);
			}
			else
			{
				body += GetContent(XMLString::transcode(element->getTextContent()));
			}
		}
	}
}