#include "XamlObjects/Rectangle.h"
#include <sstream>
namespace OpenXaml
{
	unsigned short indeces[] =
	{
		0,1,2,
		1,2,3
	};


	void Rectangle::Draw(float xmin, float xmax, float ymin, float ymax)
	{		
		float width = Width * GetScale(true);
		float height = Height * GetScale(false);
		
		GLfloat vertices[8];

		if (Rectangle::HorizontalAlignment == HorizontalAlignment::Right)
		{
			vertices[0] = xmax - width;
			vertices[2] = xmax;
			vertices[4] = xmax - width;
			vertices[6] = xmax;
		}
		else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Left)
		{
			vertices[0] = xmin;
			vertices[2] = xmin + width;
			vertices[4] = xmin;
			vertices[6] = xmin + width;
		}
		else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Center)
		{
			float mid = (xmin + xmax) / 2;
			vertices[0] = mid - width / 2;
			vertices[2] = mid + width / 2;
			vertices[4] = mid - width / 2;
			vertices[6] = mid + width / 2;
		}
		else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Stretch)
		{
			if (Width == 0)
			{
				vertices[0] = xmin;
				vertices[2] = xmax;
				vertices[4] = xmin;
				vertices[6] = xmax;
			}
			else
			{
				float mid = (xmin + xmax) / 2;
				vertices[0] = mid - width / 2;
				vertices[2] = mid + width / 2;
				vertices[4] = mid - width / 2;
				vertices[6] = mid + width / 2;
			}			
		}

		if (Rectangle::VerticalAlignment == VerticalAlignment::Top)
		{
			vertices[1] = ymax;
			vertices[3] = ymax;
			vertices[5] = ymax - height;
			vertices[7] = ymax - height;
		}
		else if (Rectangle::VerticalAlignment == VerticalAlignment::Bottom)
		{
			vertices[1] = ymin + height;
			vertices[3] = ymin + height;
			vertices[5] = ymin;
			vertices[7] = ymin;
		}
		else if (Rectangle::VerticalAlignment == VerticalAlignment::Center)
		{
			float mid = (ymin + ymax) / 2;
			vertices[1] = mid + height / 2;
			vertices[3] = mid + height / 2;
			vertices[5] = mid - height / 2;
			vertices[7] = mid - height / 2;
		}
		else if (Rectangle::VerticalAlignment == VerticalAlignment::Stretch)
		{
			if (height == 0)
			{
				vertices[1] = ymax;
				vertices[3] = ymax;
				vertices[5] = ymin;
				vertices[7] = ymin;
			}
			else
			{
				float mid = (ymin + ymax) / 2;
				vertices[1] = mid + height / 2;
				vertices[3] = mid + height / 2;
				vertices[5] = mid - height / 2;
				vertices[7] = mid - height / 2;
			}			
		}

		
		glUseProgram(Rectangle::shaderProgram);
		int vertexColorLocation = glGetUniformLocation(Rectangle::shaderProgram, "thecolor");
		float a, r, g, b;
		a = ((Fill & 0xFF000000) >> 24) / 255.0f;
		r = ((Fill & 0x00FF0000) >> 16) / 255.0f;
		g = ((Fill & 0x0000FF00) >> 8) / 255.0f;
		b = ((Fill & 0x000000FF)) / 255.0f;
		glUniform4f(vertexColorLocation, r, g, b, a);
		
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
		else
		{
			Rectangle::Width = 0;
		}
		const XMLCh *xmlHeight = element->getAttribute(XMLString::transcode("Height"));
		string height = XMLString::transcode(xmlHeight);
		if (height != "")
		{
			Rectangle::Height = stoi(height);
		}
		else
		{
			Rectangle::Height = 0;
		}
		const XMLCh *xmlFill = element->getAttribute(XMLString::transcode("Fill"));
		string fill = XMLString::transcode(xmlFill);
		if (fill != "")
		{
			if (fill[0] != '#')
			{
				throw 3;
			}
			else
			{
				std::istringstream iss(fill.substr(1, fill.size()));
				iss >> std::hex >> Rectangle::Fill;
			}
		}
		const XMLCh *xmlhalign = element->getAttribute(XMLString::transcode("HorizontalAlignment"));
		string halign = XMLString::transcode(xmlhalign);
		if (halign != "")
		{
			if (halign == "Right")
			{
				Rectangle::HorizontalAlignment = HorizontalAlignment::Right;
			}
			else if (halign == "Left")
			{
				Rectangle::HorizontalAlignment = HorizontalAlignment::Left;
			}
			else if (halign == "Center")
			{
				Rectangle::HorizontalAlignment = HorizontalAlignment::Center;
			}
			else if (halign == "Stretch")
			{
				Rectangle::HorizontalAlignment = HorizontalAlignment::Stretch;
			}
			else
			{
				throw 4;
			}
		}
		else
		{
			Rectangle::HorizontalAlignment = HorizontalAlignment::Stretch;
		}
		const XMLCh *xmlvalign = element->getAttribute(XMLString::transcode("VerticalAlignment"));
		string valign = XMLString::transcode(xmlvalign);
		if (valign != "")
		{
			if (valign == "Top")
			{
				Rectangle::VerticalAlignment = VerticalAlignment::Top;
			}
			else if (valign == "Bottom")
			{
				Rectangle::VerticalAlignment = VerticalAlignment::Bottom;
			}
			else if (valign == "Center")
			{
				Rectangle::VerticalAlignment = VerticalAlignment::Center;
			}
			else if (valign == "Stretch")
			{
				Rectangle::VerticalAlignment = VerticalAlignment::Stretch;
			}
			else
			{
				throw 4;
			}
		}
		else
		{
			Rectangle::VerticalAlignment = VerticalAlignment::Stretch;
		}
	}
}
