#include "XamlObjects/TextBlock.h"
#include "Properties/Alignment.h"
#include "Properties/TextWrapping.h"
#include "Environment.h"
#include <sstream>
#include <algorithm>
#include <glad/glad.h>
#include <gl/GLConfig.h>

namespace OpenXaml {
	void TextBlock::Draw()
	{
		this->Update();
		glBindVertexArray(TextBlock::VAO);
		glUseProgram(GL::xamlShader);
		int vertexColorLocation = glGetUniformLocation(GL::xamlShader, "thecolor");
		int modeLoc = glGetUniformLocation(GL::xamlShader, "mode");
		glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
		glUniform1i(modeLoc, 2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		for (int i = 0; i < vertexBuffers.size(); i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[i]);
			glBindTexture(GL_TEXTURE_2D, textureMap[vertexBuffers[i]]);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		}
	}
	void TextBlock::Initialize()
	{
		glGenVertexArrays(1, &(TextBlock::VAO));
		glBindVertexArray(TextBlock::VAO);
		unsigned short indeces[] =
		{
			0,1,2,
			1,2,3
		};
		glGenBuffers(1, &edgeBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
	}

	Font* font;
	void TextBlock::Update()
	{
		font = env.GetFont(FontProperties{ FontFamily, FontSize });
		glBindVertexArray(TextBlock::VAO);
		for (int i = 0; i < vertexBuffers.size(); i++)
		{
			glDeleteBuffers(1, &(vertexBuffers[i]));
		}
		vertexBuffers.clear();
		if (font == NULL)
		{
			return;
		}
		string text = Text;
		int width = 0;
		int wordWidth = 0;
		int lineCount = 0;
		int maxWidth = 0;
		int wordCount = 0;
		float fBounds = (maxCoord.x - minCoord.x) / PixelScale.x;
		static const char splitChars[] = { ' ', '-', '\t', '\n' };
		for (int i = 0; i < text.length(); i++)
		{
			char sample = text.at(i);
			wordWidth += font->operator[](sample).AdvanceX >> 6;
			if (find(begin(splitChars), end(splitChars), sample) != end(splitChars))
			{
				//we hit the end of a word
				bool lineBreak = false;
				if (sample == '\n')
				{
					lineBreak = true;
				}
				else if (TextWrapping != TextWrapping::NoWrap && width + wordWidth > fBounds)
				{
					//we need to wrap
					lineBreak = true;
				}
				if (lineBreak)
				{
					lineCount++;
					maxWidth = std::max(maxWidth, width);
					width = wordWidth;
					wordWidth = 0;
					wordCount = 0;
				}
				else
				{
					width += wordWidth;
					wordWidth = 0;
					wordCount++;
				}
			}
			else if (i == text.length() - 1)
			{
				//we need to increment once more at the end if it isn't a seperator
				lineCount++;
				width += wordWidth;
				wordWidth = 0;
				maxWidth = std::max(maxWidth, width);
			}
		}

		width = 0;
		wordWidth = 0;

		// we now know the total number of lines
		//so we do largely the same thing, except we can now render line by line
		//word by word still breaks for center justified text
		float fWidth = maxWidth * PixelScale.x;
		int height = (font->Height >> 6);
		float fHeight = height * PixelScale.y * lineCount;
		switch (VerticalAlignment)
		{
		case VerticalAlignment::Bottom:
		{
			minRendered.y = minCoord.y;
			maxRendered.y = min(maxCoord.y, minCoord.y + fHeight);
			break;
		}
		case VerticalAlignment::Top:
		{
			maxRendered.y = maxCoord.y;
			minRendered.y = max(minCoord.y, maxCoord.y - fHeight);
			break;
		}
		case VerticalAlignment::Center:
		{
			float mean = 0.5f * (maxCoord.y + minCoord.y);
			maxRendered.y = min(maxCoord.y, mean + fHeight / 2);
			minRendered.y = max(minCoord.y, mean - fHeight / 2);
			break;
		}
		case VerticalAlignment::Stretch:
		{
			maxRendered.y = maxCoord.y;
			minRendered.y = minCoord.y;
			break;
		}
		}

		switch (HorizontalAlignment)
		{
		case HorizontalAlignment::Left:
		{
			minRendered.x = minCoord.x;
			maxRendered.x = min(maxCoord.x, minCoord.x + fWidth);
			break;
		}
		case HorizontalAlignment::Right:
		{
			maxRendered.x = maxCoord.x;
			minRendered.x = max(minCoord.x, maxCoord.x - fWidth);
			break;
		}
		case HorizontalAlignment::Center:
		{
			float mean = 0.5f * (maxCoord.x + minCoord.x);
			maxRendered.x = min(maxCoord.x, mean + fWidth / 2);
			minRendered.x = max(minCoord.x, mean - fWidth / 2);
			break;
		}
		case HorizontalAlignment::Stretch:
		{
			maxRendered.x = maxCoord.x;
			minRendered.x = minCoord.x;
			break;
		}
		}

		int priorIndex = 0;
		int ppIndex = 0;
		float penX = 0;
		float penY = maxRendered.y - height * PixelScale.y;
		for (int i = 0; i < text.length(); i++)
		{
			char sample = text.at(i);
			wordWidth += font->operator[](sample).AdvanceX >> 6;
			if (find(begin(splitChars), end(splitChars), sample) != end(splitChars))
			{
				//we hit the end of a word
				bool lineBreak = false;
				if (sample == '\n')
				{
					lineBreak = true;
				}
				else if (TextWrapping != TextWrapping::NoWrap && width + wordWidth > fBounds)
				{
					//we need to wrap
					lineBreak = true;
				}
				if(lineBreak)
				{
					//there isn't enough space for the word or we need to line wrap
					//or there is a new line feed
					//we can now render it
					switch (TextAlignment)
					{
					case TextAlignment::Center:
					{
						penX = (minRendered.x + maxRendered.x) * 0.5f - width * 0.5f * PixelScale.x;
						break;
					}
					case TextAlignment::End:
					{
						penX = (maxRendered.x) - width * PixelScale.x;
						break;
					}
					case TextAlignment::Start:
					{
						penX = minRendered.x;
						break;
					}
					}
					for (int j = priorIndex; j < ppIndex; j++)
					{
						char toRender = text.at(j);
						Character ch = font->operator[](toRender);
						if (penX > maxCoord.x)
						{
							break;
						}
						RenderCharacter(toRender, penX, penY);
					}
					priorIndex = ppIndex + 1;
					penY -= height * PixelScale.y;
					if (penY < minCoord.y - height * PixelScale.y)
					{
						break;
					}
					width = wordWidth;
				}
				else
				{
					//we are short enough to keep going
					width += wordWidth;
				}
				wordWidth = 0;
				ppIndex = i;
			}
			else if (i == text.length() - 1)
			{
				//render here too
				width += wordWidth;
				wordWidth = 0;
				switch (TextAlignment)
				{
				case TextAlignment::Center:
				{
					penX = (minRendered.x + maxRendered.x) * 0.5f - width * 0.5f * PixelScale.x;
					break;
				}
				case TextAlignment::End:
				{
					penX = (maxRendered.x) - width * PixelScale.x;
					break;
				}
				case TextAlignment::Start:
				{
					penX = minRendered.x;
					break;
				}
				}
				for (int j = priorIndex; j <= i; j++)
				{
					char toRender = text.at(j);
					Character ch = font->operator[](toRender);
					if (penX > maxCoord.x)
					{
						break;
					}
					RenderCharacter(toRender, penX, penY);
				}
			}
		}
		boxWidth = (maxRendered.x - minRendered.x) / PixelScale.x; 
		boxHeight = (maxRendered.y - minRendered.y) / PixelScale.y;
	}

	void TextBlock::RenderCharacter(char toRender, float &penX, float &penY)
	{
		Character ch = font->operator[](toRender);
		if (!iscntrl(toRender))
		{
			float x0, x1, y0, y1, tx0, tx1, ty0, ty1;
			float dx0, dx1, dy0, dy1;
			dx0 = penX + ch.BearingX * PixelScale.x;
			dx1 = penX + (ch.BearingX + ch.Width) * PixelScale.x;
			dy0 = penY + ch.BearingY * PixelScale.y;
			dy1 = penY + (ch.BearingY - (int)ch.Height) * PixelScale.y;

			x0 = max(dx0, minCoord.x);
			x1 = min(dx1, maxCoord.x);
			y0 = min(dy0, maxCoord.y);
			y1 = max(dy1, minCoord.y);

			if (y1 < y0)
			{
				int a = 0;
				a++;
			}

			if (y0 < minCoord.y)
			{
				int b = 0;
				b++;
			}
			else if (y1 < minCoord.y)
			{
				int c = 0;
				c++;
			}

			float dwidth = dx1 - dx0;
			float dheight = dy1 - dy0;
			if (x0 != dx0)
			{
				tx0 = 1 - (x1 - x0) / dwidth;
			}
			else
			{
				tx0 = 0;
			}
			if (x1 != dx1)
			{
				tx1 = (x1 - x0) / dwidth;
			}
			else
			{
				tx1 = 1;
			}
			if (y0 != dy0)
			{
				if (toRender != ' ')
				{
					int a = 0; 
					a += 3;
				}
				ty0 = 1 - (y1 - y0) / dheight;
			}
			else
			{
				ty0 = 0;
			}
			if (y1 != dy1)
			{
				ty1 = (y1 - y0) / dheight;
			}
			else
			{
				ty1 = 1;
			}

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

	TextBlock::TextBlock()
	{
		boxHeight = 0;
		boxWidth = 0;
		edgeBuffer = 0;
	}

	TextBlock::~TextBlock()
	{
		//glBindVertexArray(TextBlock::VAO);
		//glDeleteVertexArrays(1, &TextBlock::VAO);
	}

	void TextBlock::setText(string text)
	{
		this->Text = text;
	}
	string TextBlock::getText()
	{
		return this->Text;
	}
	void TextBlock::setTextWrapping(OpenXaml::TextWrapping textWrapping)
	{
		this->TextWrapping = textWrapping;
	}
	TextWrapping TextBlock::getTextWrapping()
	{
		return this->TextWrapping;
	}
	void TextBlock::setFontFamily(string family)
	{
		this->FontFamily = family;
	}
	string TextBlock::getFontFamily()
	{
		return this->FontFamily;
	}
	void TextBlock::setFontSize(float size)
	{
		this->FontSize = size;
	}
	float TextBlock::getFontSize()
	{
		return this->FontSize;
	}
	void TextBlock::setFill(unsigned int fill)
	{
		this->Fill = fill;
	}
	unsigned int TextBlock::getFill()
	{
		return this->Fill;
	}
	void TextBlock::setTextAlignment(OpenXaml::TextAlignment alignment)
	{
		this->TextAlignment = alignment;
	}
	TextAlignment TextBlock::getTextAlignment()
	{
		return this->TextAlignment;
	}
	int TextBlock::getWidth()
	{
		return max(this->Width, (int)this->boxWidth);
	}
	int TextBlock::getHeight()
	{
		return max(this->Height, (int)this->boxHeight);
	}
}