#include "XamlObjects/TextBlock.h"
#include "Globals.h"

namespace OpenXaml {

	

	void TextBlock::Draw(float xmin, float xmax, float ymin, float ymax)
	{
		glUseProgram(TextBlock::shaderProgram);
		int vertexColorLocation = glGetUniformLocation(TextBlock::shaderProgram, "thecolor");
		int modeLoc = glGetUniformLocation(TextBlock::shaderProgram, "mode");
		glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
		glUniform1i(modeLoc, 2);
		float asdf = xmin;
		float fdsa = ymax;
		float x0, x1, y0, y1;

		GLfloat x = 0.0f;
		GLfloat y = 0.0f;
		GLfloat scale = 1.0f;
		for (int i = 0; i < Text.size(); i++)
		{
			char a = Text[i];
			Character ch = fa[a];
			if (a == '\n')
			{
				fdsa -= (fa.Height >> 6) * GetScale(false);
				asdf = xmin;
			}
			else if (a == '\t')
			{

			}
			else
			{
				x0 = asdf + ch.BearingX * GetScale(true);
				x1 = asdf + (ch.BearingX + ch.Width) * GetScale(true);

				if (x1 > xmax)
				{
					fdsa -= (fa.Height >> 6) * GetScale(false);
					asdf = xmin;
					x0 = asdf + ch.BearingX * GetScale(true);
					x1 = asdf + (ch.BearingX + ch.Width) * GetScale(true);
				}

				y0 = fdsa + ch.BearingY * GetScale(false);
				y1 = fdsa + (ch.BearingY - ch.Height) * GetScale(false);
				GLfloat vertices[16] = {
					x0, y0, 0,0,
					x1, y0, 1,0,
					x0, y1, 0,1,
					x1, y1, 1,1
				};

				glBindTexture(GL_TEXTURE_2D, ch.TextureID);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
			}
			asdf += (ch.AdvanceX >> 6) * GetScale(true);
			
		}
	}
	void TextBlock::Initialize(GLuint shader)
	{
		glGenVertexArrays(1, &(TextBlock::VAO));
		glBindVertexArray(TextBlock::VAO);
		unsigned short indeces[] =
		{
			0,1,2,
			1,2,3
		};
		TextBlock::shaderProgram = GL::LoadShaders();
		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &edgeBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
		glBindVertexArray(0);
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
		}

		auto text = root->getTextContent();
		TextBlock::Text = XMLString::transcode(text);
		LoadChildrenFromDOM(root);
	}

	void TextBlock::Update(float xmin, float xmax, float ymin, float ymax)
	{

	}
}