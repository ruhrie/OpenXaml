#pragma once
#include "Formatter/CppFormatter.h"
#include "internal/XamlElement.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
    namespace elements
    {
        /// A text block element
        class TextBlockElement : public XamlElement
        {
        public:
            TextBlockElement(xercesc::DOMElement *element, bool root = false);
        };
    } // namespace elements
} // namespace xut