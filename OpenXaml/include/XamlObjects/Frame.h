#ifndef FRAME_H
#define FRAME_H
#include "XamlObjects/XamlObject.h"
namespace OpenXaml {
	class Frame : public XamlObject
	{
	public:
		void Draw(float xmin, float xmax, float ymin, float ymax);
		void Draw();
		int Width = 640;
		int Height = 480;
		unsigned int Background = 0xFF000000;
		Frame();
		void Initialize(GLuint shader);
		void LoadFromDOM(DOMElement *root);
	private:
		GLuint vertexBuffer;
		GLuint edgeBuffer;
	};
}

#endif