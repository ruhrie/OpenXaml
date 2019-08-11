#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
#include <map>
namespace OpenXaml 
{
	namespace Objects
	{
		///A TextBlock object
		class TextBlock : public XamlObject
		{
		public:
			void Draw();
			void Initialize();
			void Update();
			TextBlock();
			~TextBlock();
			void setText(std::string text);
			std::string getText();
			void setTextWrapping(TextWrapping textWrapping);
			TextWrapping getTextWrapping();
			void setFontFamily(std::string family);
			std::string getFontFamily();
			void setFontSize(float size);
			float getFontSize();
			void setFill(unsigned int fill);
			unsigned int getFill();
			void setTextAlignment(TextAlignment alignment);
			TextAlignment getTextAlignment();
			int getWidth();
			int getHeight();
		private:
			unsigned int edgeBuffer;
			std::vector<unsigned int> vertexBuffers;
			std::map<unsigned int, unsigned int> textureMap;
			unsigned int boxWidth;
			unsigned int boxHeight;
			void RenderCharacter(char toRender, float& penX, float& penY);
		protected:
			std::string Text;
			TextWrapping TextWrapping = TextWrapping::WrapWholeWords;
			std::string FontFamily = "Arial";
			float FontSize = 12.0f;
			unsigned int Fill = 0x0;
			TextAlignment TextAlignment = TextAlignment::Start;
		};
	}
}
