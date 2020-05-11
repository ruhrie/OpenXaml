#include "OpenXaml/XamlObjects/ColumnDefinition.h"

namespace OpenXaml::Objects
{

    ColumnDefinition::ColumnDefinition() = default;

    int ColumnDefinition::getWidth() const
    {
        return Width;
    }
    void ColumnDefinition::setWidth(int width)
    {
        Width = width;
    }
} // namespace OpenXaml::Objects