#include "internal/GridElement.h"

using namespace std;
using namespace xercesc;
namespace xut
{
	namespace elements
	{
		GridElement::GridElement(xercesc::DOMElement* element, bool root) : XamlElement(element, root, ElementType::Grid)
		{
			init += "std::shared_ptr<OpenXaml::Objects::Grid> %name%;\n";
			bodyInit += "%name% = std::make_shared<OpenXaml::Objects::Grid>();\n";
		}
	}
}