#pragma once
#include "Formatter/CppFormatter.h"
#include "internal/XamlElement.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
    namespace elements
    {
        /// A text box element
        class TextBoxElement : public XamlElement
        {
        public:
            TextBoxElement(xercesc::DOMElement *element, bool root = false);
        };
    } // namespace elements
} // namespace xut