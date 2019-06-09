#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H
#include "XamlObjects/XamlObject.h"
#include <map>
#include <GL/Font.h>
namespace OpenXaml 
{
	class TextBlock : public XamlObject
	{
	public:
		void Draw();
		void Initialize(GLuint shader);
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
	private:
		GLuint edgeBuffer;
		vector<GLuint> vertexBuffers;
		map<GLuint, GLuint> textureMap;
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