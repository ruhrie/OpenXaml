#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "XamlObjects/XamlObject.h"
namespace OpenXaml
{
	class Rectangle : public XamlObject
	{
	public:
		Rectangle();
		void Draw();
		void Initialize();
		void Update();
		~Rectangle();
		void SetBoundingBox(coordinate min, coordinate max);
		void setFill(unsigned int fill);
		unsigned int getFill();
	private:
		unsigned int vertexBuffer;
		unsigned int edgeBuffer;
	protected:
		unsigned int Fill = 0xFF000000;
	};
}
#endif