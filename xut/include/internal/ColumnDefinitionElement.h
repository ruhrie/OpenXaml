#pragma once
#include "Formatter/CppFormatter.h"
#include "internal/XamlElement.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
    namespace elements
    {
        /// A column definition element
        class ColumnDefinitionElement : public XamlElement
        {
        public:
            ColumnDefinitionElement(xercesc::DOMElement *element, bool root = false);
        };
    } // namespace elements
} // namespace xut