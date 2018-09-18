#include <vector>
class XamlObject
{
public:
	vector<XamlObject> Children;
	interface void Draw() = 0;
};