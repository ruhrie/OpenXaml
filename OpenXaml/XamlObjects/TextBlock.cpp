#include "XamlObjects/TextBlock.h"
#include "Environment.h"
#include <sstream>
#include <algorithm>

namespace OpenXaml {
	void TextBlock::Draw()
	{
		glBindVertexArray(VAO);
		glUseProgram(TextBlock::shaderProgram);
		int vertexColorLocation = glGetUniformLocation(TextBlock::shaderProgram, "thecolor");
		int modeLoc = glGetUniformLocation(TextBlock::shaderProgram, "mode");
		glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
		glUniform1i(modeLoc, 2);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		for (int i = 0; i < vertexBuffers.size(); i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[i]);
			glBindTexture(GL_TEXTURE_2D, textureMap[vertexBuffers[i]]);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		}
	}
	void TextBlock::Initialize(GLuint shader)
	{
		Update();
	}

	void TextBlock::LoadFromDOM(DOMElement *root)
	{
		DOMNamedNodeMap* attributes = root->getAttributes();
		for (int i = 0; i < attributes->getLength(); i++)
		{
			DOMNode* item = attributes->item(i);
			const XMLCh* nameXML = item->getNodeName();
			const XMLCh* valXML = item->getNodeValue();
			string name = XMLString::transcode(nameXML);
			string value = XMLString::transcode(valXML);
			if (name == "Height")
			{
				TextBlock::Height = stoi(value);
			}
			else if (name == "Width")
			{
				TextBlock::Width = stoi(value);
			}
			else if (name == "HorizontalAlignment")
			{
				if (value == "Right")
				{
					TextBlock::HorizontalAlignment = HorizontalAlignment::Right;
				}
				else if (value == "Left")
				{
					TextBlock::HorizontalAlignment = HorizontalAlignment::Left;
				}
				else if (value == "Center")
				{
					TextBlock::HorizontalAlignment = HorizontalAlignment::Center;
				}
				else if (value == "Stretch")
				{
					TextBlock::HorizontalAlignment = HorizontalAlignment::Stretch;
				}
			}
			else if (name == "VerticalAlignment")
			{
				if (value == "Top")
				{
					TextBlock::VerticalAlignment = VerticalAlignment::Top;
				}
				else if (value == "Bottom")
				{
					TextBlock::VerticalAlignment = VerticalAlignment::Bottom;
				}
				else if (value == "Center")
				{
					TextBlock::VerticalAlignment = VerticalAlignment::Center;
				}
				else if (value == "Stretch")
				{
					TextBlock::VerticalAlignment = VerticalAlignment::Stretch;
				}
			}
			else if (name == "TextWrapping")
			{
				if (value == "None")
				{
					TextWrapping = TextWrapping::None;
				}
				else if (value == "Wrap")
				{
					TextWrapping = TextWrapping::Wrap;
				}
			}
			else if (name == "FontFamily")
			{
				TextBlock::FontFamily = value;
			}
			else if (name == "FontSize")
			{
				TextBlock::FontSize = stof(value);
			}
			else if (name == "Fill")
			{
				std::istringstream iss(value.substr(1, value.size()));
				unsigned int fill;
				iss >> std::hex >> fill;
				TextBlock::Fill = fill;
			}
			else if (name == "TextAlignment")
			{
				if (value == "Left")
				{
					TextBlock::TextAlignment = TextAlignment::Left;
				}
				else if (value == "Right")
				{
					TextBlock::TextAlignment = TextAlignment::Right;
				}
				else if (value == "Center")
				{
					TextBlock::TextAlignment = TextAlignment::Center;
				}
			}
		}

		auto text = root->getTextContent();
		TextBlock::Text = XMLString::transcode(text);

		Width.onPropertyChanged = std::bind(&TextBlock::Update, this);
		Height.onPropertyChanged = std::bind(&TextBlock::Update, this);
		Text.onPropertyChanged = std::bind(&TextBlock::Update, this);
		TextWrapping.onPropertyChanged = std::bind(&TextBlock::Update, this);
		FontFamily.onPropertyChanged = std::bind(&TextBlock::Update, this);
		FontSize.onPropertyChanged = std::bind(&TextBlock::Update, this);
		Fill.onPropertyChanged = std::bind(&TextBlock::Update, this);

		LoadChildrenFromDOM(root);
		for (int i = 0; i < Children.size(); i++)
		{
			Children[i]->SetBoundingBox(minCoord, maxCoord);
		}
	}

	void TextBlock::Update()
	{
		Font *font = env.GetFont(FontProperties{ FontFamily, FontSize });		
		glBindVertexArray(VAO);
		for (int i = 0; i < vertexBuffers.size(); i++)
		{
			glDeleteBuffers(1, &(vertexBuffers[i]));
		}
		vertexBuffers.clear();
		string text = Text;
		float xbase = minCoord.x;
		float ybase = maxCoord.y - (font->Height >> 6) * PixelScale.y;

		vector<int> widths;
		vector<int> seperators;
		static const char splitChars[] = { ' ', '-', '\t', '\n' };
		int width = 0;
		for (int i = 0; i < text.length(); i++)
		{
			if (find(begin(splitChars), end(splitChars), text[i]) == end(splitChars))
			{
				width += font->operator[](text[i]).Width;
			}
			else
			{
				widths.push_back(width);
				seperators.push_back(i);
				width = 0;
			}
		}
		vector<int> line;
		vector<vector<int>> lines;
		float fBounds = (maxCoord.x - minCoord.x)/PixelScale.x;
		int Width = 0;
		for (int i = 0; i < widths.size(); i++)
		{
			int width = widths[i];
			char seperator = text[seperators[i]];
			Width += widths[i];
			if (Width > fBounds && TextWrapping == TextWrapping::Wrap)
			{
				lines.push_back(line);
				line.clear();
				Width = widths[i];
			}
			line.push_back(i);
			if (seperator == '\n')
			{
				lines.push_back(line);
				line.clear();
				Width = 0;
			}
		}
		lines.push_back(line);
		int height = (int)lines.size() * (font->Height >> 6);
		//we now have our line seperation, so now we render each line.
		
		int maxWidth = 0;
		vector<int> lineWidths;
		for (int i = 0; i < lines.size(); i++)
		{
			line = lines[i];
			int width = 0;
			for (int j = 0; j < line.size(); j++)
			{
				width += widths[line[j]];
			}
			lineWidths.push_back(width);
			maxWidth = std::max(width, maxWidth);
			//we now have line width and can justify accordingly
		}

		//but first we get the framing rectangle's coordinates

		coordinate frameMax, frameMin;

		float fHeight = height * PixelScale.y;
		float fWidth = maxWidth * PixelScale.x;

		switch (VerticalAlignment)
		{
		case VerticalAlignment::Bottom:
		{
			frameMin.y = minCoord.y;
			frameMax.y = min(maxCoord.y, minCoord.y + fHeight);
			break;
		}
		case VerticalAlignment::Top:
		{
			frameMax.y = maxCoord.y;
			frameMin.y = max(minCoord.y, maxCoord.y - fHeight);
			break;
		}
		case VerticalAlignment::Center:
		{
			float mean = 0.5f * (maxCoord.y + minCoord.y);
			frameMax.y = min(maxCoord.y, mean + fHeight / 2);
			frameMin.y = max(minCoord.y, mean - fHeight / 2);
			break;
		}
		case VerticalAlignment::Stretch:
		{
			frameMax.y = maxCoord.y;
			frameMin.y = minCoord.y;
			break;
		}
		}
		
		switch (HorizontalAlignment)
		{
		case HorizontalAlignment::Left:
		{
			frameMin.x = minCoord.x;
			frameMax.x = min(maxCoord.x, minCoord.x + fWidth);
			break;
		}
		case HorizontalAlignment::Right:
		{
			frameMax.x = maxCoord.x;
			frameMin.x = max(minCoord.x, maxCoord.x - fWidth);
			break;
		}
		case HorizontalAlignment::Center:
		{
			float mean = 0.5f * (maxCoord.x + minCoord.x);
			frameMax.x = min(maxCoord.x, mean + fWidth / 2);
			frameMin.x = max(minCoord.x, mean - fWidth / 2);
			break;
		}
		case HorizontalAlignment::Stretch:
		{
			frameMax.x = maxCoord.x;
			frameMin.x = minCoord.x;
			break;
		}
		}

		//we now have the external rectangle dimensions, so we can actually position the text
		//start by setting the pen location
		float penX, penY;
		penY = frameMax.y - fHeight;
		for (int i = 0; i < lineWidths.size(); i++)
		{
			float lineWidth = lineWidths[i] * PixelScale.x;
			switch (TextAlignment)
			{
			case TextAlignment::Center:
			{
				penX = (frameMin.x + frameMax.x) * 0.5f - lineWidth * 0.5f;
				break;
			}
			case TextAlignment::Right:
			{
				penX = (frameMax.x) - lineWidth;
				break;
			}
			case TextAlignment::Left:
			{
				penX = frameMin.x;
				break;
			}
			}
			//we now start rendering words
			vector<int> line = lines[i];
			for (int j = 0; j < line.size(); j++)
			{
				int wordIndex = line[j];
				int length;
				int startIndex;
				if (wordIndex == 0)
				{
					startIndex = 0;
					length = seperators[wordIndex] - startIndex + 1;
				}
				else
				{
					startIndex = seperators[wordIndex - 1] + 1;
					length = seperators[wordIndex] - startIndex + 1;
				}
				string word = text.substr(startIndex, length);
				for (int k = 0; k < word.length(); k++)
				{
					char toRender = word[k];
					Character ch = font->operator[](toRender);
					if (!iscntrl(toRender))
					{
						float cWidth = ch.BearingX * PixelScale.x;
						float cHeight = ch.BearingY * PixelScale.y;
						//check if we need to render it, otherwise continue to the next character
						float x0, x1, y0, y1, tx0, tx1, ty0, ty1;
						//fill in values
						GLfloat vertices[16] = {
						x0, y0, tx0,ty0,
						x1, y0, tx1,ty0,
						x0, y1, tx0,ty1,
						x1, y1, tx1,ty1
						};
						GLuint sepBuffer;
						glGenBuffers(1, &sepBuffer);
						glBindBuffer(GL_ARRAY_BUFFER, sepBuffer);
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
						textureMap[sepBuffer] = ch.TextureID;
						vertexBuffers.push_back(sepBuffer);
					}
					penX += (ch.AdvanceX >> 6) * PixelScale.x;
				}
			}
			penY -= fHeight;
		}

		//old implementation, very wrong
		int priorSep;
		for (int i = 0; i < widths.size(); i++)
		{
			//get the word
			int width = widths[i];
			string word;
			if (i == 0)
			{
				word = text.substr(0, seperators[i]);
			}
			else
			{
				word = text.substr(priorSep + 1, seperators[i] - priorSep - 1);
			}
			priorSep = seperators[i];

			//render seperator
			char sep = text[seperators[i]];
			Character ch = font->operator[](sep);
			if (!iscntrl(sep))
			{
				float x0, x1, y0, y1, tx0, tx1, ty0, ty1;
				x0 = xbase + ch.BearingX * PixelScale.x;
				x1 = xbase + (ch.BearingX + ch.Width) * PixelScale.x;
				y0 = ybase + ch.BearingY * PixelScale.y;
				y1 = ybase + (ch.BearingY - (int)ch.Height) * PixelScale.y;
				tx0 = 0;
				tx1 = 1;
				ty0 = 0;
				ty1 = 1;

				GLfloat vertices[16] = {
						x0, y0, tx0,ty0,
						x1, y0, tx1,ty0,
						x0, y1, tx0,ty1,
						x1, y1, tx1,ty1
				};
				GLuint sepBuffer;
				glGenBuffers(1, &sepBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, sepBuffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				textureMap[sepBuffer] = ch.TextureID;
				vertexBuffers.push_back(sepBuffer);
			}
			else if (sep == '\n')
			{
				ybase -= (font->Height >> 6) * PixelScale.y;
				xbase = minCoord.x;
			}
			
			xbase += (ch.AdvanceX >> 6) * PixelScale.x;
			ybase -= (ch.AdvanceY >> 6) * PixelScale.y;

			if (xbase + (width * PixelScale.x) > maxCoord.x) //word is to long to display on line
			{
				if (TextWrapping == TextWrapping::Wrap)
				{
					ybase -= (font->Height >> 6) * PixelScale.y;
					xbase = minCoord.x;
				}
			}			

			//now render word
			for(int j = 0; j < word.length(); j++)
			{
				Character ch = font->operator[](word[j]);
				float x0, x1, y0, y1, tx0, tx1, ty0, ty1;
				x0 = xbase + ch.BearingX * PixelScale.x;
				x1 = xbase + (ch.BearingX + ch.Width) * PixelScale.x;
				y0 = ybase + ch.BearingY * PixelScale.y;
				y1 = ybase + (ch.BearingY - (int)ch.Height) * PixelScale.y;

				tx0 = 0;
				tx1 = 1;
				ty0 = 0;
				ty1 = 1;

				GLfloat vertices[16] = {
						x0, y0, tx0,ty0,
						x1, y0, tx1,ty0,
						x0, y1, tx0,ty1,
						x1, y1, tx1,ty1
				};
				GLuint characterBuffer;
				glGenBuffers(1, &characterBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, characterBuffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				vertexBuffers.push_back(characterBuffer);
				textureMap[characterBuffer] = font->operator[](word[j]).TextureID;
				xbase += (ch.AdvanceX >> 6) * PixelScale.x;
				ybase -= (ch.AdvanceY >> 6) * PixelScale.y;
			}
		}
	}

	TextBlock::TextBlock()
	{
		glGenVertexArrays(1, &(TextBlock::VAO));
		glBindVertexArray(TextBlock::VAO);
		unsigned short indeces[] =
		{
			0,1,2,
			1,2,3
		};
		TextBlock::shaderProgram = GL::LoadShaders();
		glGenBuffers(1, &edgeBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
	}

	TextBlock::~TextBlock()
	{
		glBindVertexArray(VAO);
		glDeleteVertexArrays(1, &VAO);
	}

	void TextBlock::SetBoundingBox(coordinate min, coordinate max)
	{
		minCoord = min;
		maxCoord = max;
	}
}