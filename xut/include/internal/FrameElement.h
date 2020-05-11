#pragma once
#include "Formatter/CppFormatter.h"
#include "internal/XamlElement.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
    namespace elements
    {
        ///A frame element
        class FrameElement : public XamlElement
        {
        public:
            FrameElement(xercesc::DOMElement *element, bool root = false);
        };
    } // namespace elements
} // namespace xut