#ifndef BUTTON_H
#define BUTTON_H
#include "XamlObjects/XamlObject.h"
#include "XamlObjects/TextBlock.h"
#include "XamlObjects/Rectangle.h"
#include <map>
#include <GL/Font.h>
namespace OpenXaml
{
	class Button : public XamlObject
	{
	public:
		void Draw();
		XamlProperty<string> Text;
		void Initialize(GLuint shader);
		void LoadFromDOM(DOMElement *root);
		XamlProperty<int> Height = 0;
		XamlProperty<int> Width = 0;
		XamlProperty<unsigned int> Fill = 0x33FFFFFF;
		XamlProperty<string> Content = string("Click");
		void Update();
		Button();
		~Button();
		void SetBoundingBox(coordinate min, coordinate max);
	private:
		TextBlock *Label;
		Rectangle *Frame;
	};
}
#endif