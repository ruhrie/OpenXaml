#pragma once
#include "Formatter/CppFormatter.h"
#include "internal/XamlElement.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
    namespace elements
    {
        /// A button element
        class ButtonElement : public XamlElement
        {
        public:
            ButtonElement(xercesc::DOMElement *element, bool root = false);
        };
    } // namespace elements
} // namespace xut
