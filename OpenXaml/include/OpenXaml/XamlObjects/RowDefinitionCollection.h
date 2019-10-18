#pragma once
#include "OpenXaml/XamlObjects/RowDefinition.h"
#include <vector>
namespace OpenXaml
{
    namespace Objects
    {
        ///A wrapper for row definitions
        class RowDefinitionCollection
        {
        public:
            RowDefinitionCollection();
            ~RowDefinitionCollection();
            std::vector<RowDefinition *> Children;
        };
    } // namespace Objects
} // namespace OpenXaml