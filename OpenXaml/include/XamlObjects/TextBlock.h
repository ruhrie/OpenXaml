#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H
#include "XamlObjects/XamlObject.h"
#include <map>
#include <GL/Font.h>
//https://learnopengl.com/In-Practice/Text-Rendering
namespace OpenXaml 
{
	class TextBlock : public XamlObject
	{
	public:
		void Draw();
		XamlProperty<string> Text;
		void Initialize(GLuint shader);
		void LoadFromDOM(DOMElement *root);
		XamlProperty<int> Height = 0;
		XamlProperty<int> Width = 0;
		XamlProperty<TextWrapping> TextWrapping = TextWrapping::None;
		XamlProperty<string> FontFamily = string("Arial");
		XamlProperty<float> FontSize = 12;
		void Update();
		TextBlock();
		~TextBlock();
	private:
		GLuint edgeBuffer;
		vector<GLuint> vertexBuffers;
		map<GLuint, GLuint> textureMap;
	};
}
#endif