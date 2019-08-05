#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
class GridElement : public XamlElement
{
public:
	GridElement(xercesc::DOMElement* element, bool root = false);
};