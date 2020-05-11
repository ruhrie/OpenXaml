#pragma once
#include "Formatter/CppFormatter.h"
#include "internal/XamlElement.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
    namespace elements
    {
        /// A row element
        class RowDefinitionElement : public XamlElement
        {
        public:
            RowDefinitionElement(xercesc::DOMElement *element, bool root = false);
        };
    } // namespace elements
} // namespace xut