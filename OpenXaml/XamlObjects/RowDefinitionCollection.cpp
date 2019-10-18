#include "OpenXaml/XamlObjects/RowDefinitionCollection.h"

namespace OpenXaml
{
    namespace Objects
    {
        RowDefinitionCollection::RowDefinitionCollection()
        {
        }
        RowDefinitionCollection::~RowDefinitionCollection()
        {
            for (auto row : Children)
            {
                delete row;
			}
        }
    } // namespace Objects
} // namespace OpenXaml