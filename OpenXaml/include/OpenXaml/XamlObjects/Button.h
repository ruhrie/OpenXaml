#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
#include "OpenXaml/XamlObjects/TextBlock.h"
#include "OpenXaml/XamlObjects/Rectangle.h"
#include <map>
#include <functional>
namespace OpenXaml
{
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
		void setContent(std::string content);
		std::string getContent();
		void setOnClick(std::function<void(XamlObject*)> func);
		std::function<void(XamlObject*)> getOnClick();
		void Click();
		void Click(double x, double y);
	private:
		TextBlock* Label;
		Rectangle* Frame;
	protected:
		std::string Text;
		unsigned int Fill = 0x33FFFFFF;
		std::string Content = "Click";
		std::function<void(XamlObject*)> OnClick;
	};
}