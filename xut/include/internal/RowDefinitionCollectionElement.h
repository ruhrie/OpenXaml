#pragma once
#include "Formatter/CppFormatter.h"
#include "internal/XamlElement.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
    namespace elements
    {
        /// A row collection element
        class RowDefinitionCollectionElement : public XamlElement
        {
        public:
            RowDefinitionCollectionElement(xercesc::DOMElement *element, bool root = false);
        };
    } // namespace elements
} // namespace xut