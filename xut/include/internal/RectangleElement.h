#pragma once
#include "Formatter/CppFormatter.h"
#include "internal/XamlElement.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
    namespace elements
    {
        /// A rectangle element
        class RectangleElement : public XamlElement
        {
        public:
            RectangleElement(xercesc::DOMElement *element, bool root = false);
        };
    } // namespace elements
} // namespace xut