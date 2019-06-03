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

using namespace xercesc;
using namespace std;

namespace OpenXaml
{
class XamlObject
{
  public:
	virtual void Draw() = 0;
	vector<shared_ptr<XamlObject>> Children;
	virtual void Initialize(GLuint shader) = 0;
	GLuint shaderProgram;
	XamlProperty<HorizontalAlignment> HorizontalAlignment = HorizontalAlignment::Stretch;
	XamlProperty<VerticalAlignment> VerticalAlignment = VerticalAlignment::Stretch;
	virtual void LoadFromDOM(DOMElement *root) = 0;
	GLuint VAO;
	virtual void Update() = 0;
	virtual void SetBoundingBox(coordinate min, coordinate max) = 0;
	XamlObject();
	void setPixelScale(float x, float y);
	void setPixelScale(coordinate scale);
	virtual ~XamlObject() {};
  protected:
	void LoadChildrenFromDOM(DOMElement *root);
	coordinate minCoord;
	coordinate maxCoord;
	coordinate PixelScale;
  private:
  	XamlObject& operator=(const XamlObject&);
};
} // namespace OpenXaml

#endif