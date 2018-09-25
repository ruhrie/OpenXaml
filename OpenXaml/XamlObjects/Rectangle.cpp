#include "XamlObjects/Rectangle.h"

namespace OpenXaml
{
	GLfloat minx, miny, maxx, maxy;

	unsigned short indeces[] =
	{
		0,1,2,
		1,2,3
	};


	void Rectangle::Draw(float xmin, float xmax, float ymin, float ymax)
	{
		if (minx != xmin || maxx != xmax || miny != ymin || maxy != ymax)
		{
			minx = xmin;
			maxx = xmax;
			miny = ymin;
			maxy = ymax;
			GLfloat vertices[] = {
				minx, maxy,
				maxx, maxy,
				minx, miny,
				maxx, miny
			};
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		}
		
		

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	}

	Rectangle::Rectangle()
	{
	}

	void Rectangle::Initialize()
	{
		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &edgeBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
	}
}
