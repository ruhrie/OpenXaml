#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
	namespace elements
	{
		/// A rectangle element
		class RectangleElement : public XamlElement
		{
		public:
			RectangleElement(xercesc::DOMElement* element, bool root = false);
		};
	}
}