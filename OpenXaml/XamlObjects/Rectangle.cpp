#include "XamlObjects/Rectangle.h"

namespace OpenXaml
{
	unsigned short indeces[] =
	{
		0,1,2,
		1,2,3
	};


	void Rectangle::Draw(float xmin, float xmax, float ymin, float ymax)
	{
		/*
		GLfloat vertices[8];
		int w = 0;
		int h = 0;
		float xPer, yPer;
		if (w == 0)
		{
			xPer = 0;
		}
		else
		{
			xPer = Rectangle::Width / w;
		}
		if (h == 0)
		{
			yPer = 0;
		}
		else
		{
			yPer = Rectangle::Height / h;
		}

		float currentDifX = (xmax - xmin) / 2;
		float currentDifY = (ymax - ymin) / 2;

		if (currentDifX > xPer)
		{
			vertices[0] = xmin;
			vertices[2] = xmax;
			vertices[4] = xmin;
			vertices[6] = xmax;
		}
		else
		{
			vertices[0] = xmin;
			vertices[2] = xmin + xPer * 2;
			vertices[4] = xmin;
			vertices[6] = xmin + xPer * 2;
		}
		if (currentDifY > yPer)
		{
			vertices[1] = ymin;
			vertices[3] = ymax;
			vertices[5] = ymin;
			vertices[7] = ymax;
		}
		else
		{
			vertices[1] = ymin;
			vertices[3] = ymin + yPer * 2;
			vertices[5] = ymin;
			vertices[7] = ymin + yPer * 2;
		}
		*/
		
		
		GLfloat vertices[] = {
				xmin, ymax / 2,
				xmax, ymax / 2,
				xmin, ymin / 2,
				xmax, ymin / 2
		};
		glUseProgram(Rectangle::shaderProgram);
		int vertexColorLocation = glGetUniformLocation(Rectangle::shaderProgram, "thecolor");
		glUniform4f(vertexColorLocation, 1.0f, 1.0f, 0.0f, 1.0f);
		
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		//glBindVertexArray(*Rectangle::vao);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		//glBindVertexArray(0);
	}

	Rectangle::Rectangle()
	{
	}

	void Rectangle::Initialize(GLuint shader)
	{
		Rectangle::shaderProgram = GL::LoadShaders();

		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &edgeBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
	}

	void Rectangle::GetAttributes(DOMElement *element)
	{
		const XMLCh *xmlWidth = element->getAttribute(XMLString::transcode("Width"));
		string width = XMLString::transcode(xmlWidth);
		if (width != "")
		{
			Rectangle::Width = stoi(width);
		}
		const XMLCh *xmlHeight = element->getAttribute(XMLString::transcode("Height"));
		string height = XMLString::transcode(xmlHeight);
		if (width != "")
		{
			Rectangle::Height = stoi(height);
		}
	}
}
