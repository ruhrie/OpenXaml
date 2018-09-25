#ifndef XAMLOBJECT_H
#define XAMLOBJECT_H
#include <vector>
#include <memory>
#include <glad/glad.h>

class XamlObject
{
public:
	virtual void Draw(float xmin, float xmax, float ymin, float ymax) = 0;
	std::vector<std::shared_ptr<XamlObject>> Children;
	virtual void Initialize() = 0;
};

#endif