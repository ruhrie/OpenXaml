#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
class RowDefinitionElement : public XamlElement
{
public:
	RowDefinitionElement(xercesc::DOMElement* element, bool root = false);
};