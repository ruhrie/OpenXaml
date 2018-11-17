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
		
		GLfloat vertices[16];

		if (Rectangle::HorizontalAlignment == HorizontalAlignment::Right)
		{
			vertices[0] = xmax - width;
			vertices[4] = xmax;
			vertices[8] = xmax - width;
			vertices[12] = xmax;
		}
		else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Left)
		{
			vertices[0] = xmin;
			vertices[4] = xmin + width;
			vertices[8] = xmin;
			vertices[12] = xmin + width;
		}
		else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Center)
		{
			float mid = (xmin + xmax) / 2;
			vertices[0] = mid - width / 2;
			vertices[4] = mid + width / 2;
			vertices[8] = mid - width / 2;
			vertices[12] = mid + width / 2;
		}
		else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Stretch)
		{
			if (Width == 0)
			{
				vertices[0] = xmin;
				vertices[4] = xmax;
				vertices[8] = xmin;
				vertices[12] = xmax;
			}
			else
			{
				float mid = (xmin + xmax) / 2;
				vertices[0] = mid - width / 2;
				vertices[4] = mid + width / 2;
				vertices[8] = mid - width / 2;
				vertices[12] = mid + width / 2;
			}			
		}

		if (Rectangle::VerticalAlignment == VerticalAlignment::Top)
		{
			vertices[1] = ymax;
			vertices[5] = ymax;
			vertices[9] = ymax - height;
			vertices[13] = ymax - height;
		}
		else if (Rectangle::VerticalAlignment == VerticalAlignment::Bottom)
		{
			vertices[1] = ymin + height;
			vertices[5] = ymin + height;
			vertices[9] = ymin;
			vertices[13] = ymin;
		}
		else if (Rectangle::VerticalAlignment == VerticalAlignment::Center)
		{
			float mid = (ymin + ymax) / 2;
			vertices[1] = mid + height / 2;
			vertices[5] = mid + height / 2;
			vertices[9] = mid - height / 2;
			vertices[13] = mid - height / 2;
		}
		else if (Rectangle::VerticalAlignment == VerticalAlignment::Stretch)
		{
			if (height == 0)
			{
				vertices[1] = ymax;
				vertices[5] = ymax;
				vertices[9] = ymin;
				vertices[13] = ymin;
			}
			else
			{
				float mid = (ymin + ymax) / 2;
				vertices[1] = mid + height / 2;
				vertices[5] = mid + height / 2;
				vertices[9] = mid - height / 2;
				vertices[13] = mid - height / 2;
			}			
		}
		vertices[2] = 0.0f;
		vertices[3] = 1.0f;
		vertices[6] = 1.0f;
		vertices[7] = 1.0f;
		vertices[10] = 0.0f;
		vertices[11] = 0.0f;
		vertices[14] = 1.0f;
		vertices[15] = 0.0f;
		
		glUseProgram(Rectangle::shaderProgram);
		int vertexColorLocation = glGetUniformLocation(Rectangle::shaderProgram, "thecolor");
		int modeLoc = glGetUniformLocation(Rectangle::shaderProgram, "mode");
		float a, r, g, b;
		a = ((Fill & 0xFF000000) >> 24) / 255.0f;
		r = ((Fill & 0x00FF0000) >> 16) / 255.0f;
		g = ((Fill & 0x0000FF00) >> 8) / 255.0f;
		b = ((Fill & 0x000000FF)) / 255.0f;
		glUniform4f(vertexColorLocation, r, g, b, a);
		glUniform1i(modeLoc, 0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
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

	void Rectangle::LoadFromDOM(DOMElement *root)
	{
		DOMNamedNodeMap* attributes = root->getAttributes();
		for (int i = 0; i < attributes->getLength(); i++)
		{
			DOMNode* item = attributes->item(i);
			const XMLCh* nameXML = item->getNodeName();
			const XMLCh* valXML = item->getNodeValue();
			string name = XMLString::transcode(nameXML);
			string value = XMLString::transcode(valXML);
			if (name == "Fill")
			{
				std::istringstream iss(value.substr(1, value.size()));
				iss >> std::hex >> Rectangle::Fill;
			}
			else if (name == "Height")
			{
				Rectangle::Height = stoi(value);
			}
			else if (name == "Width")
			{
				Rectangle::Width = stoi(value);
			}
			else if (name == "HorizontalAlignment")
			{
				if (value == "Right")
				{
					Rectangle::HorizontalAlignment = HorizontalAlignment::Right;
				}
				else if (value == "Left")
				{
					Rectangle::HorizontalAlignment = HorizontalAlignment::Left;
				}
				else if (value == "Center")
				{
					Rectangle::HorizontalAlignment = HorizontalAlignment::Center;
				}
				else if (value == "Stretch")
				{
					Rectangle::HorizontalAlignment = HorizontalAlignment::Stretch;
				}
			}
			else if (name == "VerticalAlignment")
			{
				if (value == "Top")
				{
					Rectangle::VerticalAlignment = VerticalAlignment::Top;
				}
				else if (value == "Bottom")
				{
					Rectangle::VerticalAlignment = VerticalAlignment::Bottom;
				}
				else if (value == "Center")
				{
					Rectangle::VerticalAlignment = VerticalAlignment::Center;
				}
				else if (value == "Stretch")
				{
					Rectangle::VerticalAlignment = VerticalAlignment::Stretch;
				}
			}
		}
		LoadChildrenFromDOM(root);
	}
}