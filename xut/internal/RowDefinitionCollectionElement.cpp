#include "internal/RowDefinitionCollectionElement.h"

using namespace std;
using namespace xercesc;

namespace xut
{
    namespace elements
    {
        RowDefinitionCollectionElement::RowDefinitionCollectionElement(xercesc::DOMElement *element, bool root) : XamlElement(element, root, ElementType::RowDefinitionCollection)
        {
            init += "std::shared_ptr<OpenXaml::Objects::RowDefinitionCollection> %name%;\n";
            bodyInit += "%name% = std::make_shared<OpenXaml::Objects::RowDefinitionCollection>();\n";
        }
    } // namespace elements
} // namespace xut