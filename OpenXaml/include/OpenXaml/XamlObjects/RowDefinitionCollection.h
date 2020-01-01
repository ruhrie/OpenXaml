#pragma once
#include "OpenXaml/XamlObjects/RowDefinition.h"
#include <memory>
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
            std::vector<std::shared_ptr<RowDefinition>> Children;
        };
    } // namespace Objects
} // namespace OpenXaml