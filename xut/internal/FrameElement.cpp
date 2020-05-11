#include "internal/FrameElement.h"
using namespace std;
using namespace xercesc;
namespace xut::elements
{
    FrameElement::FrameElement(xercesc::DOMElement *element, bool root) : XamlElement(element, root, ElementType::Frame)
    {
        if (!root)
        {
            init += "std::shared_ptr<OpenXaml::Objects::Frame> %name%;\n";
            bodyInit += "%name% = std::make_shared<OpenXaml::Objects::Frame()>;\n";
        }
        DOMAttr *fill = element->getAttributeNode(XMLString::transcode("Fill"));
        if (fill != nullptr)
        {
            body += GetFill(fill, root);
        }
    }
} // namespace xut::elements