#include "xml/DomLoader.h"
#include "xml/UID.h"
#include <sstream>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/util/XMLString.hpp>
using namespace xercesc;
using namespace OpenXaml;
using namespace OpenXaml::Objects;
using namespace std;

namespace xut
{
    shared_ptr<XamlObject> LoadXaml(DOMElement *element)
    {
        const XMLCh *xmlString = element->getTagName();
        string name = XMLString::transcode(xmlString);
        shared_ptr<XamlObject> result;
        if (name == "Frame")
        {
            result = DomToFrame(element);
        }
        else if (name == "Button")
        {
            result = DomToButton(element);
        }
        else if (name == "Rectangle")
        {
            result = DomToRectangle(element);
        }
        else if (name == "TextBlock")
        {
            result = DomToTextBlock(element);
        }
        else
        {
            throw 2;
        }
        return result;
    }

    shared_ptr<Frame> DomToFrame(DOMElement *element)
    {
        shared_ptr<Frame> result;
        DOMNamedNodeMap *attributes = element->getAttributes();
        for (uint32_t i = 0; i < attributes->getLength(); i++)
        {
            DOMNode *item = attributes->item(i);
            const XMLCh *nameXML = item->getNodeName();
            const XMLCh *valXML = item->getNodeValue();
            string name = XMLString::transcode(nameXML);
            string value = XMLString::transcode(valXML);
            if (name == "Fill")
            {
                std::istringstream iss(value.substr(1, value.size()));
                unsigned int val;
                iss >> std::hex >> val;
                result->setFill(val);
            }
            else if (name == "Height")
            {
                result->setHeight(stoi(value));
            }
            else if (name == "Width")
            {
                result->setWidth(stoi(value));
            }
        }
        size_t childCount = element->getChildElementCount();
        auto *children = element->getChildNodes();
        for (uint32_t i = 0; i < childCount; i++)
        {
            auto *child = children->item(i);
            result->Children.push_back(LoadXaml((DOMElement *)child));
        }
        return result;
    }

    shared_ptr<Button> DomToButton(DOMElement *element)
    {
        shared_ptr<Button> result;

        DOMNamedNodeMap *attributes = element->getAttributes();
        for (uint32_t i = 0; i < attributes->getLength(); i++)
        {
            DOMNode *item = attributes->item(i);
            const XMLCh *nameXML = item->getNodeName();
            const XMLCh *valXML = item->getNodeValue();
            string name = XMLString::transcode(nameXML);
            string value = XMLString::transcode(valXML);
            if (name == "Height")
            {
                result->setHeight(stoi(value));
            }
            else if (name == "Width")
            {
                result->setWidth(stoi(value));
            }
            else if (name == "HorizontalAlignment")
            {
                if (value == "Right")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Right);
                }
                else if (value == "Left")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Left);
                }
                else if (value == "Center")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Center);
                }
                else if (value == "Stretch")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Stretch);
                }
            }
            else if (name == "VerticalAlignment")
            {
                if (value == "Top")
                {
                    result->setVerticalAlignment(VerticalAlignment::Top);
                }
                else if (value == "Bottom")
                {
                    result->setVerticalAlignment(VerticalAlignment::Bottom);
                }
                else if (value == "Center")
                {
                    result->setVerticalAlignment(VerticalAlignment::Center);
                }
                else if (value == "Stretch")
                {
                    result->setVerticalAlignment(VerticalAlignment::Stretch);
                }
            }
            else if (name == "Fill")
            {
                std::istringstream iss(value.substr(1, value.size()));
                unsigned int fill;
                iss >> std::hex >> fill;
                result->setFill(fill);
            }
            else if (name == "Text")
            {
                result->setText(value);
            }
        }

        const auto *text = element->getTextContent();
        result->setText(XMLString::transcode(text));
        size_t childCount = element->getChildElementCount();
        auto *children = element->getChildNodes();
        for (uint32_t i = 0; i < childCount; i++)
        {
            auto *child = children->item(i);
            result->Children.push_back(LoadXaml((DOMElement *)child));
        }
        return result;
    }

    shared_ptr<OpenXaml::Objects::Rectangle> DomToRectangle(DOMElement *element)
    {
        shared_ptr<OpenXaml::Objects::Rectangle> result;

        DOMNamedNodeMap *attributes = element->getAttributes();
        for (uint32_t i = 0; i < attributes->getLength(); i++)
        {
            DOMNode *item = attributes->item(i);
            const XMLCh *nameXML = item->getNodeName();
            const XMLCh *valXML = item->getNodeValue();
            string name = XMLString::transcode(nameXML);
            string value = XMLString::transcode(valXML);
            if (name == "Fill")
            {
                std::istringstream iss(value.substr(1, value.size()));
                unsigned int fill;
                iss >> std::hex >> fill;
                result->setFill(fill);
            }
            else if (name == "Height")
            {
                result->setHeight(stoi(value));
            }
            else if (name == "Width")
            {
                result->setWidth(stoi(value));
            }
            else if (name == "HorizontalAlignment")
            {
                if (value == "Right")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Right);
                }
                else if (value == "Left")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Left);
                }
                else if (value == "Center")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Center);
                }
                else if (value == "Stretch")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Stretch);
                }
            }
            else if (name == "VerticalAlignment")
            {
                if (value == "Top")
                {
                    result->setVerticalAlignment(VerticalAlignment::Top);
                }
                else if (value == "Bottom")
                {
                    result->setVerticalAlignment(VerticalAlignment::Bottom);
                }
                else if (value == "Center")
                {
                    result->setVerticalAlignment(VerticalAlignment::Center);
                }
                else if (value == "Stretch")
                {
                    result->setVerticalAlignment(VerticalAlignment::Stretch);
                }
            }
        }

        size_t childCount = element->getChildElementCount();
        auto *children = element->getChildNodes();
        for (uint32_t i = 0; i < childCount; i++)
        {
            auto *child = children->item(i);
            result->Children.push_back(LoadXaml((DOMElement *)child));
        }
        return result;
    }

    shared_ptr<OpenXaml::Objects::TextBlock> DomToTextBlock(xercesc::DOMElement *element)
    {
        shared_ptr<TextBlock> result;

        DOMNamedNodeMap *attributes = element->getAttributes();
        for (uint32_t i = 0; i < attributes->getLength(); i++)
        {
            DOMNode *item = attributes->item(i);
            const XMLCh *nameXML = item->getNodeName();
            const XMLCh *valXML = item->getNodeValue();
            string name = XMLString::transcode(nameXML);
            string value = XMLString::transcode(valXML);

            if (name == "Height")
            {
                result->setHeight(stoi(value));
            }
            else if (name == "Width")
            {
                result->setWidth(stoi(value));
            }
            else if (name == "HorizontalAlignment")
            {
                if (value == "Right")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Right);
                }
                else if (value == "Left")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Left);
                }
                else if (value == "Center")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Center);
                }
                else if (value == "Stretch")
                {
                    result->setHorizontalAlignment(HorizontalAlignment::Stretch);
                }
            }
            else if (name == "VerticalAlignment")
            {
                if (value == "Top")
                {
                    result->setVerticalAlignment(VerticalAlignment::Top);
                }
                else if (value == "Bottom")
                {
                    result->setVerticalAlignment(VerticalAlignment::Bottom);
                }
                else if (value == "Center")
                {
                    result->setVerticalAlignment(VerticalAlignment::Center);
                }
                else if (value == "Stretch")
                {
                    result->setVerticalAlignment(VerticalAlignment::Stretch);
                }
            }
            else if (name == "TextWrapping")
            {
                if (value == "NoWrap")
                {
                    result->setTextWrapping(TextWrapping::NoWrap);
                }
                else if (value == "Wrap")
                {
                    result->setTextWrapping(TextWrapping::Wrap);
                }
            }
            else if (name == "FontFamily")
            {
                result->setFontFamily(value);
            }
            else if (name == "FontSize")
            {
                result->setFontSize(stof(value));
            }
            else if (name == "Fill")
            {
                std::istringstream iss(value.substr(1, value.size()));
                unsigned int fill;
                iss >> std::hex >> fill;
                result->setFill(fill);
            }
            else if (name == "TextAlignment")
            {
                if (value == "Start")
                {
                    result->setTextAlignment(TextAlignment::Start);
                }
                else if (value == "End")
                {
                    result->setTextAlignment(TextAlignment::End);
                }
                else if (value == "Center")
                {
                    result->setTextAlignment(TextAlignment::Center);
                }
            }
        }

        const auto *text = element->getTextContent();
        result->setText(XMLString::transcode(text));

        size_t childCount = element->getChildElementCount();
        auto *children = element->getChildNodes();
        for (uint32_t i = 0; i < childCount; i++)
        {
            auto *child = children->item(i);
            result->Children.push_back(LoadXaml((DOMElement *)child));
        }

        return result;
    }
} // namespace xut