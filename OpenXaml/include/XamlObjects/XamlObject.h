#ifndef XAMLOBJECT_H
#define XAMLOBJECT_H
#include <vector>
#include <memory>
#include <glad/glad.h>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <string>
#include "GL/GLConfig.h"
#include "Properties/HorizontalAlignment.h"
#include "Properties/VerticalAlignment.h"
#include "XamlObjects/XamlProperty.h"
#include "XamlObjects/Coordinate.h"
#include "Globals.h"
using namespace xercesc;
using namespace std;
class XamlObject
{
public:
	virtual void Draw(float xmin, float xmax, float ymin, float ymax) = 0;
	std::vector<std::shared_ptr<XamlObject>> Children;
	virtual void Initialize(GLuint shader) = 0;
	GLuint shaderProgram;
	char HorizontalAlignment = HorizontalAlignment::Stretch;
	char VerticalAlignment = VerticalAlignment::Stretch;
	virtual void LoadFromDOM(DOMElement *root) = 0;
	static shared_ptr<XamlObject> ParseObject(DOMElement* obj);
	GLuint VAO;
	virtual void Update(float xmin, float xmax, float ymin, float ymax) = 0;
private:
	coordinate minCoord;
	coordinate maxCoord;
protected:
	void LoadChildrenFromDOM(DOMElement *root);
};

#endif