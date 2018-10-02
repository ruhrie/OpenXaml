#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Frame.h"

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
	glUniform4f(vertexColorLocation, 0.0f, 1.0f, 1.0f, 1.0f);
	
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

}