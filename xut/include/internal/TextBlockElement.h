#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
class TextBlockElement : public XamlElement
{
public:
	TextBlockElement(xercesc::DOMElement* element, bool root = false);
};