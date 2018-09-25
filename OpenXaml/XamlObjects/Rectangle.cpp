
#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Rectangle.h"
#include <glad/glad.h>
#include <GL/GLConfig.h>
	GLfloat vertices[] = {
		 -1.0f,  1.0f,
		 1.0f, 1.0f,
		 -1.0f, -1.0f,
		 1.0f, -1.0f
	};

	unsigned int indeces[] =
	{
		0,1,2,
		1,2,3
	};
	
	
	void Rectangle::Draw(float xmin, float xmax, float ymin, float ymax)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	Rectangle::Rectangle()
	{
		//glBindBuffer(GL_ARRAY_BUFFER, GL::vertexBuffer);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
		//glGenBuffers(1, &rectBuffer);
		//glGenBuffers(1, &vbo);
	}