#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
	namespace elements
	{
		/// A column definition element
		class ColumnDefinitionElement : public XamlElement
		{
		public:
			ColumnDefinitionElement(xercesc::DOMElement* element, bool root = false);
		};
	}
}