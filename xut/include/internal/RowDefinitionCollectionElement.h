#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
class RowDefinitionCollectionElement : public XamlElement
{
public:
	RowDefinitionCollectionElement(xercesc::DOMElement* element, bool root = false);
};