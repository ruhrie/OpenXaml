#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
class ButtonElement : public XamlElement
{
public:
	ButtonElement(xercesc::DOMElement* element, bool root = false);
};