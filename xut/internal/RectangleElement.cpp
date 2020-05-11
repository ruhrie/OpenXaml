#include "internal/RectangleElement.h"

using namespace std;
using namespace xercesc;
namespace xut::elements
{
    RectangleElement::RectangleElement(xercesc::DOMElement *element, bool root) : XamlElement(element, root, ElementType::Rectangle)
    {
        init += "std::shared_ptr<OpenXaml::Objects::Rectangle> %name%;\n";
        bodyInit += "%name% = std::make_shared<OpenXaml::Objects::Rectangle>();\n";
        DOMAttr *fill = element->getAttributeNode(XMLString::transcode("Fill"));
        if (fill != nullptr)
        {
            body += GetFill(fill, root);
        }
    }
} // namespace xut::elements