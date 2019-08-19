#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
#include "OpenXaml/XamlObjects/TextBlock.h"
#include "OpenXaml/XamlObjects/Rectangle.h"
#include <map>
#include <functional>
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
			void setOnClick(std::function<void(XamlObject*)> func);
			std::function<void(XamlObject*)> getOnClick();
			void Click();
			void Click(double x, double y);
		private:
			TextBlock* Label;
			Rectangle* Frame;
		protected:
			unsigned int Fill = 0x33FFFFFF;
			std::string Text = "Click";
			std::function<void(XamlObject*)> OnClick;
		};
	}	
}