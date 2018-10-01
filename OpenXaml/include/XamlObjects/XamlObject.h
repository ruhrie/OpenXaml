#ifndef XAMLOBJECT_H
#define XAMLOBJECT_H
#include <vector>
#include <memory>
#include <glad/glad.h>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <string>
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
};

#endif