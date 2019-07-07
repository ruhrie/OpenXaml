#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H
#include "XamlObjects/XamlObject.h"
#include <map>
namespace OpenXaml 
{
	class TextBlock : public XamlObject
	{
	public:
		void Draw();
		void Initialize();
		void LoadFromDOM(DOMElement *root);
		void Update();
		TextBlock();
		~TextBlock();
		void SetBoundingBox(coordinate min, coordinate max);
		void setText(string text);
		string getText();
		void setTextWrapping(TextWrapping textWrapping);
		TextWrapping getTextWrapping();
		void setFontFamily(string family);
		string getFontFamily();
		void setFontSize(float size);
		float getFontSize();
		void setFill(unsigned int fill);
		unsigned int getFill();
		void setTextAlignment(TextAlignment alignment);
		TextAlignment getTextAlignment();
		int getWidth();
		int getHeight();
	private:
		unsigned int edgeBuffer;
		vector<unsigned int> vertexBuffers;
		map<unsigned int, unsigned int> textureMap;
		unsigned int boxWidth;
		unsigned int boxHeight;
	protected:
		string Text;
		TextWrapping TextWrapping = TextWrapping::None;
		string FontFamily = "Arial";
		float FontSize = 12.0;
		unsigned int Fill = 0;
		TextAlignment TextAlignment = TextAlignment::Left;
	};
}
#endif