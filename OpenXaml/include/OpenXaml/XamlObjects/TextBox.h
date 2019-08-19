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
			~TextBox();
			void Initialize();
			void Draw();
			void Update();
			void setPlaceholderText(std::string placeholderText);
			std::string getPlaceholderText();
			void setText(std::string text);
			std::string getText();
		private:
			std::string Text = "";
			std::string PlaceholderText = "Placeholder";
			Rectangle* Frame;
			TextBlock* PlaceholderTextTextBlock;
			TextBlock* TextTextBlock;
		};
	}
}