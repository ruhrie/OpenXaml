#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
namespace OpenXaml
{
    namespace Objects
    {
        ///A renderable rectangle object
        class Rectangle : public XamlObject
        {
        public:
            Rectangle();
            void Draw();
            void Initialize();
            void Update();
            ~Rectangle();
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