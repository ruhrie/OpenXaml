#include "OpenXaml/XamlObjects/ColumnDefinitionCollection.h"

namespace OpenXaml
{
    namespace Objects
    {

        ColumnDefinitionCollection::ColumnDefinitionCollection()
        {
        }
        ColumnDefinitionCollection::~ColumnDefinitionCollection()
        {
            for (auto col : Children)
            {
                delete col;
			}
        }
    } // namespace Objects
} // namespace OpenXaml