#ifndef XAMLOBJECT_H
#define XAMLOBJECT_H
#include <vector>
#include <memory>
#include <glad/glad.h>
#include <functional>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <string>
#include "GL/GLConfig.h"
#include "Properties/Alignment.h"
#include "Properties/TextWrapping.h"
#include "XamlObjects/XamlProperty.h"
#include "XamlObjects/Coordinate.h"
#include "Globals.h"
using namespace xercesc;
using namespace std;
class XamlObject
{
public:
	virtual void Draw() = 0;
	std::vector<std::shared_ptr<XamlObject>> Children;
	virtual void Initialize(GLuint shader) = 0;
	GLuint shaderProgram;
	XamlProperty<HorizontalAlignment> HorizontalAlignment = HorizontalAlignment::Stretch;
	XamlProperty<VerticalAlignment> VerticalAlignment = VerticalAlignment::Stretch;
	virtual void LoadFromDOM(DOMElement *root) = 0;
	static XamlObject* ParseObject(DOMElement* obj);
	GLuint VAO;
	virtual void Update() = 0;
	void SetBoundingBox(coordinate min, coordinate max);
	XamlObject();
protected:
	void LoadChildrenFromDOM(DOMElement *root);
	coordinate minCoord;
	coordinate maxCoord;
};

#endif