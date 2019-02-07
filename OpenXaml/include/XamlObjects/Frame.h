#ifndef FRAME_H
#define FRAME_H
#include "XamlObjects/XamlObject.h"

namespace OpenXaml {
	class Frame : public XamlObject
	{
	public:
		void Draw();
		XamlProperty<int> Width = 640;
		XamlProperty<int> Height = 480;
		XamlProperty<unsigned int> Fill = 0xFF000000;
		Frame();
		static Frame* ParseFrame(DOMElement *obj);
		void Initialize(GLuint shader);
		void LoadFromDOM(xercesc_3_2::DOMElement *root);
		void Update();
		~Frame();
		void SetBoundingBox(coordinate min, coordinate max);
	private:
		GLuint vertexBuffer;
		GLuint edgeBuffer;
	};
}

#endif