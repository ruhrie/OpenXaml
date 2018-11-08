#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Frame.h"
#include <sstream>
unsigned short indeces[] =
{
	0,1,2,
	1,2,3
};

Frame::Frame()
{

}

void Frame::Draw(float xmin, float xmax, float ymin, float ymax)
{
	glUseProgram(Frame::shaderProgram);
	int vertexColorLocation = glGetUniformLocation(Frame::shaderProgram, "thecolor");

	float a, r, g, b;
	a = ((Background & 0xFF000000) >> 24) / 255.0f;
	r = ((Background & 0x00FF0000) >> 16) / 255.0f;
	g = ((Background & 0x0000FF00) >> 8) / 255.0f;
	b = ((Background & 0x000000FF)) / 255.0f;
	glUniform4f(vertexColorLocation, r, g, b, a);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
	
	//glBindVertexArray(*Frame::vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	//glBindVertexArray(0);
	for (unsigned int i = 0; i < Children.size(); i++)
	{
		Children[i]->Draw(xmin, xmax, ymin, ymax);
	}
}

void Frame::Draw()
{
	Frame::Draw(-1.0f, 1.0f, -1.0f, 1.0f);
}

void Frame::Initialize(GLuint shader)
{
	Frame::shaderProgram = GL::LoadShaders();
	GLfloat vertices[] = {
				-1, 1,
				1, 1,
				-1, -1,
				1, -1
	};

	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &edgeBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	for (unsigned int i = 0; i < Children.size(); i++)
	{
		Children[i]->Initialize(shader);
	}
}

void Frame::GetAttributes(DOMElement *element)
{
	const XMLCh *xmlWidth = element->getAttribute(XMLString::transcode("Width"));
	string width = XMLString::transcode(xmlWidth);
	if (width != "")
	{
		Frame::Width = stoi(width);
	}
	const XMLCh *xmlHeight = element->getAttribute(XMLString::transcode("Height"));
	string height = XMLString::transcode(xmlHeight);
	if (width != "")
	{
		Frame::Height = stoi(height);
	}
	const XMLCh *xmlBackground = element->getAttribute(XMLString::transcode("Background"));
	string background = XMLString::transcode(xmlBackground);
	if (background != "")
	{
		if (background[0] != '#')
		{
			throw 3;
		}
		else
		{
			std::istringstream iss(background.substr(1, background.size()));
			iss >> std::hex >> Frame::Background;
		}
	}
}