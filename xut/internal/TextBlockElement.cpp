#include "internal/TextBlockElement.h"

using namespace std;
using namespace xercesc;

namespace xut::elements
{
    TextBlockElement::TextBlockElement(xercesc::DOMElement *element, bool root) : XamlElement(element, root, ElementType::TextBlock)
    {
        init += "std::shared_ptr<OpenXaml::Objects::TextBlock> %name%;\n";
        bodyInit += "%name% = std::make_shared<OpenXaml::Objects::TextBlock>();\n";
        DOMAttr *fill = element->getAttributeNode(XMLString::transcode("Fill"));
        if (fill != nullptr)
        {
            body += GetFill(fill, root);
        }
        DOMAttr *textAlignment = element->getAttributeNode(XMLString::transcode("TextAlignment"));
        if (textAlignment != nullptr)
        {
            body += GetTextAlignment(textAlignment);
        }
        DOMAttr *fontSize = element->getAttributeNode(XMLString::transcode("FontSize"));
        if (fontSize != nullptr)
        {
            body += GetFontSize(fontSize);
        }
        DOMAttr *fontFamily = element->getAttributeNode(XMLString::transcode("FontFamily"));
        if (fontFamily != nullptr)
        {
            body += GetFontFamily(fontFamily);
        }
        DOMAttr *textWrapping = element->getAttributeNode(XMLString::transcode("TextWrapping"));
        if (textWrapping != nullptr)
        {
            body += GetTextWrapping(textWrapping);
        }
        DOMAttr *text = element->getAttributeNode(XMLString::transcode("Text"));
        if (text != nullptr)
        {
            body += GetText(text);
        }
        else
        {
            body += GetText(XMLString::transcode(element->getTextContent()));
        }
    }
} // namespace xut::elements