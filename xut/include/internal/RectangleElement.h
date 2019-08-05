#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
class RectangleElement : public XamlElement
{
public:
	RectangleElement(xercesc::DOMElement* element, bool root = false);
};