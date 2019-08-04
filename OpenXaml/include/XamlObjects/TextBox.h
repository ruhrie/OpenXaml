#pragma once
#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Rectangle.h"
#include "XamlObjects/TextBlock.h"
namespace OpenXaml
{
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