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
		void Initialize(GLuint shader);
		void LoadFromDOM(DOMElement *root);
		void Update();
		Button();
		~Button();
		void SetBoundingBox(coordinate min, coordinate max);
		void setFill(unsigned int fill);
		unsigned int getFill();
		void setContent(string content);
		string getContent();
	private:
		TextBlock *Label;
		Rectangle *Frame;
	protected:
		string Text;
		unsigned int Fill = 0x33FFFFFF;
		string Content = "Click";
	};
}
#endif