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
using namespace xercesc;
using namespace std;
class XamlObject
{
public:
	virtual void Draw(float xmin, float xmax, float ymin, float ymax) = 0;
	std::vector<std::shared_ptr<XamlObject>> Children;
	virtual void Initialize(GLuint shader) = 0;
	virtual void GetAttributes(DOMElement *element) = 0;
	GLuint shaderProgram;
	void SetScale(float scale, bool isHorizontal);
	float GetScale(bool horizontal);
	char HorizontalAlignment = HorizontalAlignment::Stretch;
	char VerticalAlignment = VerticalAlignment::Stretch;
	virtual void LoadFromDOM(DOMElement *root) = 0;
	static shared_ptr<XamlObject> ParseObject(DOMElement* obj);
private:
	float xScale;
	float yScale;
protected:
	void LoadChildrenFromDOM(DOMElement *root);
};

#endif