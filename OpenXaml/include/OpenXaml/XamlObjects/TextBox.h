#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
#include "OpenXaml/XamlObjects/Rectangle.h"
#include "OpenXaml/XamlObjects/TextBlock.h"
namespace OpenXaml
{
	namespace Objects
	{
		///A TextBox object. Incomplete
		class TextBox : public XamlObject
		{
		public:
			TextBox();
		private:
			Rectangle* Frame;
			TextBlock* Placeholder;
			TextBlock* Content;
		};
	}
}