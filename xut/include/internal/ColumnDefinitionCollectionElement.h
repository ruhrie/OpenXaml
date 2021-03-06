#pragma once
#include "Formatter/CppFormatter.h"
#include "internal/XamlElement.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
    namespace elements
    {
        /// A column definition collection element
        class ColumnDefinitionCollectionElement : public XamlElement
        {
        public:
            ColumnDefinitionCollectionElement(xercesc::DOMElement *element, bool root = false);
        };
    } // namespace elements
} // namespace xut