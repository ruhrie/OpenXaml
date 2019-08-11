#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
	namespace elements
	{
		/// A text block element
		class TextBlockElement : public XamlElement
		{
		public:
			TextBlockElement(xercesc::DOMElement* element, bool root = false);
		};
	}
}