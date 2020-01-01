#pragma once
#include "OpenXaml/XamlObjects/ColumnDefinitionCollection.h"
#include "OpenXaml/XamlObjects/RowDefinitionCollection.h"
#include "OpenXaml/XamlObjects/XamlObject.h"
#include <memory>
namespace OpenXaml
{
    namespace Objects
    {
        ///A grid for rendering xaml objects
        class Grid : public XamlObject
        {
        public:
            void Draw();
            Grid();
            void Initialize();
            void Update();
            ~Grid();
            std::shared_ptr<ColumnDefinitionCollection> ColumnDefinitions;
            std::shared_ptr<RowDefinitionCollection> RowDefinitions;

        protected:
            void SetBoundingBox(vec2<float> min, vec2<float> max);
        };
    } // namespace Objects
} // namespace OpenXaml
