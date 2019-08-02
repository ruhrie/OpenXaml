#ifndef XAMLOBJECT_H
#define XAMLOBJECT_H
#include <vector>
#include <functional>
#include <string>
#include "Properties/Alignment.h"
#include "Properties/TextWrapping.h"
#include "XamlObjects/Coordinate.h"
using namespace std;

namespace OpenXaml
{
class XamlObject
{
  public:
	virtual void Draw() = 0;
	vector<XamlObject *> Children;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	bool IsContained(coordinate input);
	XamlObject();
	void setPixelScale(float x, float y);
	void setPixelScale(coordinate scale);
	~XamlObject();
	void setHorizontalAlignment(HorizontalAlignment alignment);
	void setVerticalAlignment(VerticalAlignment alignment);
	HorizontalAlignment getHorizontalAlignment();
	VerticalAlignment getVerticalAlignment();
	void setHeight(int height);
	int getHeight();
	void setWidth(int width);
	int getWidth(); 
  protected:
	void SetBoundingBox(coordinate min, coordinate max);
	coordinate minCoord;
	coordinate maxCoord;
	coordinate minRendered;
	coordinate maxRendered;
	coordinate PixelScale;
	int Height;
	int Width;
	HorizontalAlignment HorizontalAlignment = HorizontalAlignment::Stretch;
	VerticalAlignment VerticalAlignment = VerticalAlignment::Stretch;
	unsigned int VAO;
	std::vector<XamlObject*> DerivedElements;
	coordinate GetMaxRendered();
	coordinate GetMinRendered();
  private:
  	XamlObject& operator=(const XamlObject&);		
};
} // namespace OpenXaml

#endif