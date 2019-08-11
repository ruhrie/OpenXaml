#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
	namespace elements
	{
		/// A row element
		class RowDefinitionElement : public XamlElement
		{
		public:
			RowDefinitionElement(xercesc::DOMElement* element, bool root = false);
		};
	}
}