#pragma once
#include "OpenXaml/XamlObjects/ColumnDefinition.h"
#include <memory>
#include <vector>
namespace OpenXaml
{
    namespace Objects
    {
        ///A renderable wrapper for column definitions
        class ColumnDefinitionCollection
        {
        public:
            ColumnDefinitionCollection();
            ~ColumnDefinitionCollection();
            std::vector<std::shared_ptr<ColumnDefinition>> Children;
        };
    } // namespace Objects
} // namespace OpenXaml