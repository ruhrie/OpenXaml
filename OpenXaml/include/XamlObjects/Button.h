#pragma once
#include "XamlObjects/XamlObject.h"
#include "XamlObjects/TextBlock.h"
#include "XamlObjects/Rectangle.h"
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
		void SetBoundingBox(coordinate min, coordinate max);
		void setFill(unsigned int fill);
		unsigned int getFill();
		void setContent(string content);
		string getContent();
		void setOnClick(std::function<void(XamlObject*)> func);
		function<void(XamlObject*)> getOnClick();
	private:
		TextBlock *Label;
		Rectangle *Frame;
	protected:
		string Text;
		unsigned int Fill = 0x33FFFFFF;
		string Content = "Click";
		function<void(XamlObject*)> OnClick;
	};
}