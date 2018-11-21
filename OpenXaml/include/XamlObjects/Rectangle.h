#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "XamlObjects/XamlObject.h"
namespace OpenXaml
{
	class Rectangle : public XamlObject
	{
	public:
		int Width = 0;
		int Height = 0;
		Rectangle();
		void Draw();
		void Initialize(GLuint shader);
		unsigned int Fill = 0xFF000000;
		void LoadFromDOM(DOMElement *root);
		void Update();
		~Rectangle();
	private:
		GLuint vertexBuffer;
		GLuint edgeBuffer;
	};
}
#endif