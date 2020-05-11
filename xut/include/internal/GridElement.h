#pragma once
#include "Formatter/CppFormatter.h"
#include "internal/XamlElement.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
    namespace elements
    {
        /// A grid element
        class GridElement : public XamlElement
        {
        public:
            GridElement(xercesc::DOMElement *element, bool root = false);
        };
    } // namespace elements
} // namespace xut