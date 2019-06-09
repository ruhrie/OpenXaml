#ifndef FRAME_H
#define FRAME_H
#include "XamlObjects/XamlObject.h"

namespace OpenXaml {
	class Frame : public XamlObject
	{
	public:
		void Draw();
		Frame();
		static Frame* ParseFrame(DOMElement *obj);
		void Initialize(GLuint shader);
		void LoadFromDOM(xercesc_3_2::DOMElement *root);
		void Update();
		~Frame();
		void SetBoundingBox(coordinate min, coordinate max);
		void setFill(unsigned int fill);
		unsigned int getFill();
	private:
		GLuint vertexBuffer;
		GLuint edgeBuffer;
	protected:
		unsigned int Fill = 0xFF000000;
	};
}

#endif