#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Frame.h"
#include <sstream>

namespace OpenXaml
{
	

	Frame::Frame()
	{

	}

	void Frame::Draw(float xmin, float xmax, float ymin, float ymax)
	{
		glUseProgram(Frame::shaderProgram);
		int vertexColorLocation = glGetUniformLocation(Frame::shaderProgram, "thecolor");
		int modeLoc = glGetUniformLocation(Frame::shaderProgram, "mode");
		float a, r, g, b;
		a = ((Background & 0xFF000000) >> 24) / 255.0f;
		r = ((Background & 0x00FF0000) >> 16) / 255.0f;
		g = ((Background & 0x0000FF00) >> 8) / 255.0f;
		b = ((Background & 0x000000FF)) / 255.0f;
		glUniform4f(vertexColorLocation, r, g, b, a);
		glUniform1i(modeLoc, 0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

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
					-1, 1, 0, 1,
					1, 1, 1, 1,
					-1, -1, 0, 0,
					1, -1, 1, 0
		};

		unsigned short indeces[] =
		{
			0,1,2,
			1,2,3
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

	void Frame::LoadFromDOM(DOMElement *root)
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
				iss >> std::hex >> Frame::Background;
			}
			else if (name == "Height")
			{
				Frame::Height = stoi(value);
			}
			else if (name == "Width")
			{
				Frame::Width = stoi(value);
			}
		}
		LoadChildrenFromDOM(root);
	}
}
