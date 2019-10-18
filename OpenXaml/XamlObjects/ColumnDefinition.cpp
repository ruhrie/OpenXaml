#include "OpenXaml/XamlObjects/ColumnDefinition.h"

namespace OpenXaml
{
    namespace Objects
    {

        ColumnDefinition::ColumnDefinition()
        {
        }
        ColumnDefinition::~ColumnDefinition()
        {
        }
        int ColumnDefinition::getWidth()
        {
            return Width;
        }
        void ColumnDefinition::setWidth(int width)
        {
            Width = width;
        }
    } // namespace Objects
} // namespace OpenXaml