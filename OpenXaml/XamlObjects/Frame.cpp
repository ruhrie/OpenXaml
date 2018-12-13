#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Frame.h"
#include <sstream>

namespace OpenXaml
{
	Frame::Frame()
	{
		glGenVertexArrays(1, &(Frame::VAO));
		glBindVertexArray(Frame::VAO);
		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &edgeBuffer);
		minCoord.x = -1;
		minCoord.y = -1;
		maxCoord.x = 1;
		maxCoord.y = 1;

		Width.onPropertyChanged = std::bind(&Frame::Update, this);
		Height.onPropertyChanged = std::bind(&Frame::Update, this);
		Fill.onPropertyChanged = std::bind(&Frame::Update, this);
	}

	void Frame::Draw()
	{
		glBindVertexArray(Frame::VAO);
		glUseProgram(Frame::shaderProgram);
		int vertexColorLocation = glGetUniformLocation(Frame::shaderProgram, "thecolor");
		int modeLoc = glGetUniformLocation(Frame::shaderProgram, "mode");
		float a, r, g, b;
		a = ((Fill & 0xFF000000) >> 24) / 255.0f;
		r = ((Fill & 0x00FF0000) >> 16) / 255.0f;
		g = ((Fill & 0x0000FF00) >> 8) / 255.0f;
		b = ((Fill & 0x000000FF)) / 255.0f;
		glUniform4f(vertexColorLocation, r, g, b, a);
		glUniform1i(modeLoc, 0);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		for (unsigned int i = 0; i < Children.size(); i++)
		{
			Children[i]->Draw();
		}
	}

	void Frame::Initialize(GLuint shader)
	{
		glBindVertexArray(Frame::VAO);
		Frame::shaderProgram = shader;
		float vertices[] = {
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

		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
		Update();
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
				unsigned int val;
				iss >> std::hex >> val;
				Frame::Fill = val;
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
		for (int i = 0; i < Children.size(); i++)
		{
			Children[i]->SetBoundingBox(minCoord, maxCoord);
		}
	}

	void Frame::Update()
	{

	}

	Frame::~Frame()
	{
		glBindVertexArray(Frame::VAO);
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &edgeBuffer);
		glDeleteVertexArrays(1, &VAO);
	}

	OpenXaml::Frame Frame::ParseFrame(DOMElement * obj)
{
	const XMLCh *xmlString = obj->getTagName();
	string name = XMLString::transcode(xmlString);
	Frame result;
	if (name == "Frame")
	{
		result = OpenXaml::Frame();
	}
	else
	{
		throw 2;
	}
	result.LoadFromDOM(obj);
	return result;
}
}
