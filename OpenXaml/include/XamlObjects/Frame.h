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
		void Initialize(GLuint shader);
		void LoadFromDOM(DOMElement *root);
		void Update();
	private:
		GLuint vertexBuffer;
		GLuint edgeBuffer;
	};
}

#endif