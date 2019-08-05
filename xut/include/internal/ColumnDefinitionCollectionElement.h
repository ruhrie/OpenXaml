#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
class ColumnDefinitionCollectionElement : public XamlElement
{
public:
	ColumnDefinitionCollectionElement(xercesc::DOMElement* element, bool root = false);
};