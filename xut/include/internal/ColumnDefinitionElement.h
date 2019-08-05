#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
class ColumnDefinitionElement : public XamlElement
{
public:
	ColumnDefinitionElement(xercesc::DOMElement* element, bool root = false);
};