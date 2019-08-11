#include "internal/GridElement.h"

using namespace std;
using namespace xercesc;
namespace xut
{
	namespace elements
	{
		GridElement::GridElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::Grid)
		{
			init += "OpenXaml::Objects::Grid* %name%;\n";
			term += "delete %name%;\n";
			bodyInit += "%name% = new OpenXaml::Objects::Grid();\n";
		}
	}
}