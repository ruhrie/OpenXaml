#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include <memory>
class XamlObject
{
	public:
		virtual void Draw(float xmin, float xmax, float ymin, float ymax) = 0;
		std::vector<std::shared_ptr<XamlObject>> Children;
};
#endif