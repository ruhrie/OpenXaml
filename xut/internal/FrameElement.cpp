#include "internal/FrameElement.h"
using namespace std;
using namespace xercesc;
FrameElement::FrameElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::Frame)
{
	if (!root)
	{
		init += "OpenXaml::Frame* %name%;\n";
		term += "delete %name%;\n";
		bodyInit += "%name% = new OpenXaml::Frame();\n";
	}
	DOMAttr* fill = element->getAttributeNode(XMLString::transcode("Fill"));
	if (fill != NULL)
	{
		body += GetFill(fill , root);
	}
}