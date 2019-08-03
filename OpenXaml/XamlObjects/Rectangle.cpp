#include "XamlObjects/Rectangle.h"
#include <glad/glad.h>
#include <GL/GLConfig.h>
#include <sstream>
#include <algorithm>
namespace OpenXaml
{
	void Rectangle::Draw()
	{
		this->Update();
		glBindVertexArray(Rectangle::VAO);
		glUseProgram(GL::xamlShader);
		int vertexColorLocation = glGetUniformLocation(GL::xamlShader, "thecolor");
		int modeLoc = glGetUniformLocation(GL::xamlShader, "mode");
		float a, r, g, b;
		a = ((Fill & 0xFF000000) >> 24) / 255.0f;
		r = ((Fill & 0x00FF0000) >> 16) / 255.0f;
		g = ((Fill & 0x0000FF00) >> 8) / 255.0f;
		b = ((Fill & 0x000000FF)) / 255.0f;
		glUniform4f(vertexColorLocation, r, g, b, a);
		glUniform1i(modeLoc, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	}

	Rectangle::Rectangle()
	{
	}

	void Rectangle::Initialize()
	{
		glGenVertexArrays(1, &(Rectangle::VAO));
		glBindVertexArray(Rectangle::VAO);
		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &edgeBuffer);
		unsigned short indeces[] =
		{
			0,1,2,
			1,2,3
		};
		glBindVertexArray(Rectangle::VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
		glBindVertexArray(0);
	}

	void Rectangle::Update()
	{
		glBindVertexArray(Rectangle::VAO);
		float width = Width * PixelScale.x;
		float height = Height * PixelScale.y;

		GLfloat vertices[16];

		if (Rectangle::HorizontalAlignment == HorizontalAlignment::Right)
		{
			vertices[0] = std::max(maxCoord.x - width, minCoord.x);
			vertices[4] = maxCoord.x;
			vertices[8] = std::max(maxCoord.x - width, minCoord.x);
			vertices[12] = maxCoord.x;
		}
		else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Left)
		{
			vertices[0] = minCoord.x;
			vertices[4] = std::min(minCoord.x + width, maxCoord.x);
			vertices[8] = minCoord.x;
			vertices[12] = std::min(minCoord.x + width, maxCoord.x);
		}
		else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Center)
		{
			float mid = (minCoord.x + maxCoord.x) / 2;
			vertices[0] = std::min(mid - width / 2, minCoord.x);
			vertices[4] = std::max(mid + width / 2, maxCoord.x);
			vertices[8] = std::min(mid - width / 2, minCoord.x);
			vertices[12] = std::max(mid + width / 2, maxCoord.x);
		}
		else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Stretch)
		{
			if (Width == 0)
			{
				vertices[0] = minCoord.x;
				vertices[4] = maxCoord.x;
				vertices[8] = minCoord.x;
				vertices[12] = maxCoord.x;
			}
			else
			{
				float mid = (minCoord.x + maxCoord.x) / 2;
				vertices[0] = std::min(mid - width / 2, minCoord.x);
				vertices[4] = std::max(mid + width / 2, maxCoord.x);
				vertices[8] = std::min(mid - width / 2, minCoord.x);
				vertices[12] = std::max(mid + width / 2, maxCoord.x);
			}
		}

		if (Rectangle::VerticalAlignment == VerticalAlignment::Top)
		{
			vertices[1] = maxCoord.y;
			vertices[5] = maxCoord.y;
			vertices[9] = std::max(maxCoord.y - height, minCoord.y);
			vertices[13] = std::max(maxCoord.y - height, minCoord.y);
		}
		else if (Rectangle::VerticalAlignment == VerticalAlignment::Bottom)
		{
			vertices[1] = std::min(minCoord.y + height, maxCoord.y);
			vertices[5] = std::min(minCoord.y + height, maxCoord.y);
			vertices[9] = minCoord.y;
			vertices[13] = minCoord.y;
		}
		else if (Rectangle::VerticalAlignment == VerticalAlignment::Center)
		{
			float mid = (minCoord.y + maxCoord.y) / 2;
			vertices[1] = mid + height / 2;
			vertices[5] = mid + height / 2;
			vertices[9] = mid - height / 2;
			vertices[13] = mid - height / 2;
		}
		else if (Rectangle::VerticalAlignment == VerticalAlignment::Stretch)
		{
			if (height == 0)
			{
				vertices[1] = maxCoord.y;
				vertices[5] = maxCoord.y;
				vertices[9] = minCoord.y;
				vertices[13] = minCoord.y;
			}
			else
			{
				float mid = (minCoord.y + maxCoord.y) / 2;
				vertices[1] = std::min(mid + height / 2, minCoord.y);
				vertices[5] = std::min(mid + height / 2, minCoord.y);
				vertices[9] = std::max(mid - height / 2, maxCoord.y);
				vertices[13] = std::max(mid - height / 2, maxCoord.y);
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
		minRendered = { vertices[0] ,vertices[9] };
		maxRendered = { vertices[4],vertices[1] };
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	}

	Rectangle::~Rectangle()
	{
		glBindVertexArray(Rectangle::VAO);
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &edgeBuffer);
		glDeleteVertexArrays(1, &(Rectangle::VAO));
	}

	void Rectangle::setFill(unsigned int fill)
	{
		this->Fill = fill;
	}
	unsigned int Rectangle::getFill()
	{
		return this->Fill;
	}
}