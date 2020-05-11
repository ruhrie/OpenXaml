#include "OpenXaml/XamlObjects/RowDefinition.h"

namespace OpenXaml::Objects
{
    RowDefinition::RowDefinition() = default;

    void RowDefinition::setHeight(int height)
    {
        Height = height;
    }
    int RowDefinition::getHeight() const
    {
        return Height;
    }
} // namespace OpenXaml::Objects
