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
		float fdsa = 0.0f;
		float x0, x1, y0, y1;

		GLfloat x = 0.0f;
		GLfloat y = 0.0f;
		GLfloat scale = 1.0f;
		for (int i = 0; i < Text.size(); i++)
		{
			char a = Text[i];
			Character ch = fa[a];
			x0 = asdf + ch.BearingX * GetScale(true);
			x1 = asdf + (ch.BearingX + ch.Width) * GetScale(true);
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
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) (2 * sizeof(float)));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
			/*
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			*/
			asdf += (ch.Advance >> 6) * GetScale(true);
		}
	}
	void TextBlock::GetAttributes(DOMElement *element)
	{
		auto bodyConst = element->getTextContent();
		string body = XMLString::transcode(bodyConst);
		Text = body;
	}
	void TextBlock::Initialize(GLuint shader)
	{
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
	}
}