#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
#include <map>
#include <OpenXaml/GL/Font.h>
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
			void setText(std::u32string text);
			void setText(std::string text);
			std::u32string getText();
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
			coordinate getDesiredDimensions();

		private:
			unsigned int edgeBuffer;
			unsigned int vertexBuffer;
			std::map<unsigned int, unsigned int> textureMap;
			unsigned int boxWidth;
			unsigned int boxHeight;
			void RenderCharacter(UChar ch, float& penX, float& penY, float* vertexBuffer, unsigned short* edgeBuffer, int &index);
			Font* font;
			unsigned int glyphCount = 0;

		protected:
			std::u32string Text;
			TextWrapping TextWrapping = TextWrapping::WrapWholeWords;
			std::string FontFamily = "Arial";
			float FontSize = 12.0f;
			unsigned int Fill = 0x0;
			TextAlignment TextAlignment = TextAlignment::Start;
		};
	} // namespace Objects
} // namespace OpenXaml
