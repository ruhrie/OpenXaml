#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "XamlObjects/XamlObject.h"
namespace OpenXaml
{
	class Rectangle : public XamlObject
	{
	public:
		int Width = 100;
		int Height = 100;
		Rectangle();
		void Draw(float xmin, float xmax, float ymin, float ymax);
		void Initialize();
		void GetAttributes(DOMElement *element);
	private:
		GLuint vertexBuffer;
		GLuint edgeBuffer;
	};
}
#endif