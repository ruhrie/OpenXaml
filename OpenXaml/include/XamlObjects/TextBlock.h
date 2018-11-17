#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H
#include "XamlObjects/XamlObject.h"
//https://learnopengl.com/In-Practice/Text-Rendering
namespace OpenXaml 
{
	class TextBlock : public XamlObject
	{
	public:
		void Draw(float xmin, float xmax, float ymin, float ymax);
		string Text;
		void GetAttributes(DOMElement *element);
		void Initialize(GLuint shader);
		void LoadFromDOM(DOMElement *root);
		int Height;
		int Width;
	private:
		GLuint vertexBuffer;
		GLuint edgeBuffer;
	};
}
#endif