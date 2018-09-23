#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
class XamlObject
{
	public:
		virtual void Draw() = 0;
		std::vector<XamlObject *> Children;
};
#endif