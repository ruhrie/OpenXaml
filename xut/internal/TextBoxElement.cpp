#include "internal/TextBoxElement.h"

using namespace std;
using namespace xercesc;

namespace xut
{
	namespace elements
	{
		TextBoxElement::TextBoxElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::TextBox)
		{
			init += "OpenXaml::Objects::TextBox* %name%;\n";
			//term += "delete %name%;\n";
			bodyInit += "%name% = new OpenXaml::Objects::TextBox();\n";
			DOMAttr* text = element->getAttributeNode(XMLString::transcode("Text"));
			if (text != NULL)
			{
				body += GetText(text);
			}
			DOMAttr* placeholderText = element->getAttributeNode(XMLString::transcode("PlaceholderText"));
			if (placeholderText != NULL)
			{
				body += GetPlaceholderText(placeholderText);
			}
		}
	}
}