#pragma once
#include <string>
#include <vector>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
namespace xut
{
    namespace elements
    {
        /// An enum of xut parsable xaml elements
        enum class ElementType
        {
            None,
            Frame,
            Button,
            Rectangle,
            TextBlock,
            Grid,
            RowDefinition,
            ColumnDefinition,
            RowDefinitionCollection,
            ColumnDefinitionCollection,
            TextBox
        };

        ///The base class of all xut xaml elements
        class XamlElement
        {
        public:
            std::vector<XamlElement *> Children;
            std::string Name = "";
            ~XamlElement();
            bool Public = false;
            std::string Initializer;
            std::string Body;
            std::string Terminator;
            std::string ChildEnumerator;
            std::string ExternalFunctions;
            std::string BodyInitializer;
            ElementType Type = ElementType::None;
            static XamlElement *GetXamlElement(xercesc::DOMElement *element, bool root = false);
            void SetContent();
            XamlElement(xercesc::DOMElement *element, bool root = false, ElementType type = ElementType::None);

        protected:
            XamlElement();
            bool Root = false;
            std::string init;
            std::string term;
            std::string body;
            std::string ext;
            std::string bodyInit;
        };
    } // namespace elements
} // namespace xut