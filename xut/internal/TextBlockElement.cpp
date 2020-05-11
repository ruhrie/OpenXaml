#include "internal/TextBlockElement.h"

using namespace std;
using namespace xercesc;

namespace xut
{
    namespace elements
    {
        TextBlockElement::TextBlockElement(xercesc::DOMElement *element, bool root) : XamlElement(element, root, ElementType::TextBlock)
        {
            init += "std::shared_ptr<OpenXaml::Objects::TextBlock> %name%;\n";
            bodyInit += "%name% = std::make_shared<OpenXaml::Objects::TextBlock>();\n";
            DOMAttr *fill = element->getAttributeNode(XMLString::transcode("Fill"));
            if (fill != NULL)
            {
                body += GetFill(fill, root);
            }
            DOMAttr *textAlignment = element->getAttributeNode(XMLString::transcode("TextAlignment"));
            if (textAlignment != NULL)
            {
                body += GetTextAlignment(textAlignment);
            }
            DOMAttr *fontSize = element->getAttributeNode(XMLString::transcode("FontSize"));
            if (fontSize != NULL)
            {
                body += GetFontSize(fontSize);
            }
            DOMAttr *fontFamily = element->getAttributeNode(XMLString::transcode("FontFamily"));
            if (fontFamily != NULL)
            {
                body += GetFontFamily(fontFamily);
            }
            DOMAttr *textWrapping = element->getAttributeNode(XMLString::transcode("TextWrapping"));
            if (textWrapping != NULL)
            {
                body += GetTextWrapping(textWrapping);
            }
            DOMAttr *text = element->getAttributeNode(XMLString::transcode("Text"));
            if (text != NULL)
            {
                body += GetText(text);
            }
            else
            {
                body += GetText(XMLString::transcode(element->getTextContent()));
            }
        }
    } // namespace elements
} // namespace xut