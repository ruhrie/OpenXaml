#include "XamlObjects/TextBlock.h"
#include "Globals.h"

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
		}

		auto text = root->getTextContent();
		TextBlock::Text = XMLString::transcode(text);
		LoadChildrenFromDOM(root);
		for (int i = 0; i < Children.size(); i++)
		{
			Children[i]->SetBoundingBox(minCoord, maxCoord);
		}
	}

	void TextBlock::Update()
	{
		glBindVertexArray(VAO);
		for (int i = 0; i < vertexBuffers.size(); i++)
		{
			glDeleteBuffers(1, &(vertexBuffers[i]));
		}
		vertexBuffers.clear();
		string text = Text;
		float xbase = minCoord.x;
		float ybase = maxCoord.y - (fa.Height >> 6) * PixelScale.y;

		vector<int> widths;
		vector<int> seperators;
		static char splitChars[] = { ' ', '-', '\t', '\n' };
		int width = 0;
		for (int i = 0; i < text.length(); i++)
		{
			if (find(begin(splitChars), end(splitChars), text[i]) == end(splitChars))
			{
				width += fa[text[i]].Width;
			}
			else
			{
				widths.push_back(width);
				seperators.push_back(i);
				width = 0;
			}
		}
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
			Character ch = fa[sep];
			if (!iscntrl(sep))
			{
				float x0, x1, y0, y1, tx0, tx1, ty0, ty1;
				x0 = xbase + ch.BearingX * PixelScale.x;
				x1 = xbase + (ch.BearingX + ch.Width) * PixelScale.x;
				y0 = ybase + ch.BearingY * PixelScale.y;
				y1 = ybase + (ch.BearingY - ch.Height) * PixelScale.y;
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
				ybase -= (fa.Height >> 6) * PixelScale.y;
				xbase = minCoord.x;
			}
			
			xbase += (ch.AdvanceX >> 6) * PixelScale.x;
			ybase -= (ch.AdvanceY >> 6) * PixelScale.y;

			if (xbase + (width * PixelScale.x) > maxCoord.x) //word is to long to display on line
			{
				if (TextWrapping == TextWrapping::Wrap)
				{
					ybase -= (fa.Height >> 6) * PixelScale.y;
					xbase = minCoord.x;
				}
			}			

			//now render word
			for(int j = 0; j < word.length(); j++)
			{
				Character ch = fa[word[j]];
				float x0, x1, y0, y1, tx0, tx1, ty0, ty1;
				x0 = xbase + ch.BearingX * PixelScale.x;
				x1 = xbase + (ch.BearingX + ch.Width) * PixelScale.x;
				y0 = ybase + ch.BearingY * PixelScale.y;
				y1 = ybase + (ch.BearingY - ch.Height) * PixelScale.y;

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
				textureMap[characterBuffer] = fa[word[j]].TextureID;
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
		Width.onPropertyChanged = std::bind(&TextBlock::Update, this);
		Height.onPropertyChanged = std::bind(&TextBlock::Update, this);
		Text.onPropertyChanged = std::bind(&TextBlock::Update, this);
		TextWrapping.onPropertyChanged = std::bind(&TextBlock::Update, this);
		glBindVertexArray(0);
	}

	TextBlock::~TextBlock()
	{
		glBindVertexArray(VAO);
		glDeleteVertexArrays(1, &VAO);
	}
}