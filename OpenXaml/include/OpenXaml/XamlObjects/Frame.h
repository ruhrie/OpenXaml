#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"

namespace OpenXaml
{
    namespace Objects
    {
        /// The renderable root for xaml pages
        class Frame : public XamlObject
        {
        public:
            void Draw();
            Frame();
            void Initialize();
            void Update();
            ~Frame();
            void setFill(unsigned int fill);
            unsigned int getFill() const;

        private:
            unsigned int vertexBuffer;
            unsigned int edgeBuffer;

        protected:
            unsigned int Fill = 0xFF000000;
        };
    } // namespace Objects
} // namespace OpenXaml
