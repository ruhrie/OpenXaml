#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "XamlObjects/XamlObject.h"
namespace OpenXaml
{
	class Rectangle : public XamlObject
	{
	public:
		XamlProperty<int> Width = 0;
		XamlProperty<int> Height = 0;
		Rectangle();
		void Draw();
		void Initialize(GLuint shader);
		XamlProperty<unsigned int> Fill = 0xFF000000;
		void LoadFromDOM(DOMElement *root);
		void Update();
		~Rectangle();
		void SetBoundingBox(coordinate min, coordinate max);
	private:
		GLuint vertexBuffer;
		GLuint edgeBuffer;
	};
}
#endif