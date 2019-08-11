#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
	namespace elements
	{
		/// A grid element
		class GridElement : public XamlElement
		{
		public:
			GridElement(xercesc::DOMElement* element, bool root = false);
		};
	}
}