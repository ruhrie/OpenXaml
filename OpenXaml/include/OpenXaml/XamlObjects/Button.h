#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
#include "OpenXaml/XamlObjects/TextBlock.h"
#include "OpenXaml/XamlObjects/Rectangle.h"
#include <map>
namespace OpenXaml
{
	namespace Objects
	{
		///A renderable xaml button
		class Button : public XamlObject
		{
		public:
			void Draw();
			void Initialize();
			void Update();
			Button();
			~Button();
			void setFill(unsigned int fill);
			unsigned int getFill();
			void setText(std::string content);
			std::string getText();
		private:
			TextBlock* Label;
			Rectangle* Frame;
		protected:
			unsigned int Fill = 0x33FFFFFF;
			std::string Text = "Click";
		};
	}	
}