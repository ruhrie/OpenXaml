#include "OpenXaml/XamlObjects/RowDefinition.h"

namespace OpenXaml
{
    namespace Objects
    {
        RowDefinition::RowDefinition()
        {
        }
        RowDefinition::~RowDefinition()
        {
        }
        void RowDefinition::setHeight(int height)
        {
            Height = height;
        }
        int RowDefinition::getHeight()
        {
            return Height;
        }
    } // namespace Objects
} // namespace OpenXaml
