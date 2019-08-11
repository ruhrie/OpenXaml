#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
	namespace elements
	{
		///A frame element
		class FrameElement : public XamlElement
		{
		public:
			FrameElement(xercesc::DOMElement* element, bool root = false);
		};
	}
}