#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
class FrameElement : public XamlElement
{
public:
	FrameElement(xercesc::DOMElement* element, bool root = false);
};