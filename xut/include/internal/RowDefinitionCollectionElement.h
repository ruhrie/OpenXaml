#pragma once
#include "internal/XamlElement.h"
#include "Formatter/CppFormatter.h"
#include <xercesc/dom/DOMElement.hpp>
namespace xut
{
	namespace elements
	{
		/// A row collection element
		class RowDefinitionCollectionElement : public XamlElement
		{
		public:
			RowDefinitionCollectionElement(xercesc::DOMElement* element, bool root = false);
		};
	}
}