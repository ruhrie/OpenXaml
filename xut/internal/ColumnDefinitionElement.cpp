#include "internal/ColumnDefinitionElement.h"

using namespace std;
using namespace xercesc;
namespace xut
{
    namespace elements
    {
        ColumnDefinitionElement::ColumnDefinitionElement(xercesc::DOMElement *element, bool root) : XamlElement(element, root, ElementType::ColumnDefinition)
        {
            init += "std::shared_ptr<OpenXaml::Objects::ColumnDefinition> %name%;\n";
            bodyInit += "%name% = std::make_shared<OpenXaml::Objects::ColumnDefinition>();\n";
        }
    } // namespace elements
} // namespace xut