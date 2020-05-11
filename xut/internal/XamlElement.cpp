#include "internal/XamlElement.h"
#include "internal/XamlElements.h"
#include "xml/UID.h"
#include <iostream>
#include <sstream>
using namespace std;
using namespace xercesc;

namespace xut
{
    namespace elements
    {
        XamlElement::XamlElement()
        {
        }

        XamlElement *XamlElement::GetXamlElement(xercesc::DOMElement *element, bool root)
        {
            const XMLCh *xmlString = element->getTagName();
            string name = xercesc::XMLString::transcode(xmlString);
            XamlElement *result;
            if (name == "Frame")
            {
                result = new FrameElement(element, root);
            }
            else if (name == "Grid")
            {
                result = new GridElement(element, root);
            }
            else if (name == "RowDefinitionCollection")
            {
                result = new RowDefinitionCollectionElement(element, root);
            }
            else if (name == "RowDefinition")
            {
                result = new RowDefinitionElement(element, root);
            }
            else if (name == "ColumnDefinitionCollection")
            {
                result = new ColumnDefinitionCollectionElement(element, root);
            }
            else if (name == "ColumnDefinition")
            {
                result = new ColumnDefinitionElement(element, root);
            }
            else if (name == "Button")
            {
                result = new ButtonElement(element, root);
            }
            else if (name == "Rectangle")
            {
                result = new RectangleElement(element, root);
            }
            else if (name == "TextBlock")
            {
                result = new TextBlockElement(element, root);
            }
            else if (name == "TextBox")
            {
                result = new TextBoxElement(element, root);
            }
            else
            {
                throw 2;
            }
            result->SetContent();
            return result;
        }

        XamlElement::XamlElement(xercesc::DOMElement *element, bool root, ElementType type)
        {
            Type = type;
            DOMAttr *name = element->getAttributeNode(XMLString::transcode("Name"));
            string nameStr = "";
            if (name != NULL)
            {
                body += GetName(name, root);
                nameStr = GetNameString(name);
                Public = true;
            }
            else
            {
                nameStr = "var_" + to_string(GetUID());
            }
            DOMAttr *height = element->getAttributeNode(XMLString::transcode("Height"));
            if (height != NULL)
            {
                body += GetHeight(height, root);
            }
            DOMAttr *width = element->getAttributeNode(XMLString::transcode("Width"));
            if (width != NULL)
            {
                body += GetWidth(width, root);
            }
            DOMAttr *horAlign = element->getAttributeNode(XMLString::transcode("HorizontalAlignment"));
            if (horAlign != NULL)
            {
                body += GetHorizontalAlignment(horAlign, root);
            }
            DOMAttr *verAlign = element->getAttributeNode(XMLString::transcode("VerticalAlignment"));
            if (verAlign != NULL)
            {
                body += GetVerticalAlignment(verAlign, root);
            }
            DOMAttr *gridRow = element->getAttributeNode(XMLString::transcode("Grid.Row"));
            if (gridRow != NULL)
            {
                body += GetGridRow(gridRow);
            }
            DOMAttr *gridColumn = element->getAttributeNode(XMLString::transcode("Grid.Column"));
            if (gridColumn != NULL)
            {
                body += GetGridColumn(gridColumn);
            }
            DOMAttr *vis = element->getAttributeNode(XMLString::transcode("Visibility"));
            if (vis != NULL)
            {
                body += GetVisibility(vis);
            }
            DOMAttr *onClick = element->getAttributeNode(XMLString::transcode("OnClick"));
            if (onClick != NULL)
            {
                ext += GetClickSigniture(onClick);
                body += GetClickCall(onClick);
            }
            DOMAttr *margin = element->getAttributeNode(XMLString::transcode("Margin"));
            if (margin != NULL)
            {
                body += GetMargin(margin);
            }
            Name = nameStr;
            size_t childCount = element->getChildElementCount();
            auto children = element->getChildNodes();
            for (uint32_t i = 0; i < childCount; i++)
            {
                auto child = children->item(i);
                XamlElement *childElement = XamlElement::GetXamlElement((DOMElement *)child, false);
                if (root)
                {
                    ChildEnumerator += "Children.push_back(" + childElement->Name + ");\n";
                }
                else
                {
                    if (Type == ElementType::Grid)
                    {
                        if (childElement->Type == ElementType::ColumnDefinitionCollection)
                        {
                            ChildEnumerator += Name + "->ColumnDefinitions = " + childElement->Name + ";\n";
                        }
                        else if (childElement->Type == ElementType::RowDefinitionCollection)
                        {
                            ChildEnumerator += Name + "->RowDefinitions = " + childElement->Name + ";\n";
                        }
                        else
                        {
                            ChildEnumerator += Name + "->Children.push_back(" + childElement->Name + ");\n";
                        }
                    }
                    else
                    {
                        ChildEnumerator += Name + "->Children.push_back(" + childElement->Name + ");\n";
                    }
                }
                Children.push_back(childElement);
            }
        }

        void XamlElement::SetContent()
        {
            size_t pos = 0;
            while ((pos = init.find("%name%", 0)) != std::string::npos)
            {
                init.replace(pos, 6, Name);
            }
            while ((pos = body.find("%name%", 0)) != std::string::npos)
            {
                body.replace(pos, 6, Name);
            }
            while ((pos = term.find("%name%", 0)) != std::string::npos)
            {
                term.replace(pos, 6, Name);
            }
            while ((pos = bodyInit.find("%name%", 0)) != std::string::npos)
            {
                bodyInit.replace(pos, 6, Name);
            }
            Initializer = init;
            Body = body;
            BodyInitializer = bodyInit;
            Terminator = term;
            ExternalFunctions = ext;
        }

        XamlElement::~XamlElement()
        {
            for (XamlElement *element : Children)
            {
                delete element;
            }
        }
    } // namespace elements
} // namespace xut