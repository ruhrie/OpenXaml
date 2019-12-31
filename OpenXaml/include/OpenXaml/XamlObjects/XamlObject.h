#pragma once
#include "OpenXaml/Properties/Alignment.h"
#include "OpenXaml/Properties/TextWrapping.h"
#include "OpenXaml/Properties/Thickness.h"
#include "OpenXaml/Properties/Visibility.h"
#include "OpenXaml/XamlObjects/vec2.h"
#include <functional>
#include <string>
#include <vector>

namespace OpenXaml
{
    namespace Objects
    {
        /// An abstract base class for all Xaml Objects
        class XamlObject
        {
        public:
            virtual void Draw() = 0;            ///The draw call which actually renders the object.
            std::vector<XamlObject *> Children; ///The child objects to the current xaml element.
            virtual void Initialize() = 0;      ///Currently responsible for initializing the OpenGL attributes. Due to be removed soon.
            virtual void Update();
            XamlObject();
            virtual ~XamlObject();
            void setHorizontalAlignment(HorizontalAlignment alignment);
            void setVerticalAlignment(VerticalAlignment alignment);
            HorizontalAlignment getHorizontalAlignment();
            VerticalAlignment getVerticalAlignment();
            void setHeight(int height);
            int getHeight();
            void setWidth(int width);
            int getWidth();
            int getColumn();
            int getRow();
            void setRow(int row);
            void setColumn(int column);
            void setVisibility(OpenXaml::Visibility visibility);
            OpenXaml::Visibility getVisibility();
            virtual void SetBoundingBox(vec2<float> min, vec2<float> max); ///Sets the bounding box for rendering the object (not where it actually renders).
            void Click();
            void Click(double x, double y);
            virtual void setOnClick(std::function<void(XamlObject *)> func);
            std::function<void(XamlObject *)> getOnClick();
            vec2<float> GetMaxRendered(); ///Gets the upper right corner of the actually rendered object
            vec2<float> GetMaxRenderable();
            vec2<float> GetMinRendered(); ///Gets the lower left corner of the actually rendered object
            vec2<float> GetMinRenderable();
            virtual void AnimationUpdate(int arg);
            Thickness Margin;
        protected:
            vec2<float> minCoord;
            vec2<float> maxCoord;
            vec2<float> minRendered;
            vec2<float> maxRendered;
            int Height;
            int Width;
            OpenXaml::Visibility Visibility;
            HorizontalAlignment HorizontalAlignment = HorizontalAlignment::Stretch;
            VerticalAlignment VerticalAlignment = VerticalAlignment::Stretch;
            unsigned int VAO;
            std::vector<XamlObject *> DerivedElements;
            std::function<void(XamlObject *)> OnClick;

        private:
            XamlObject &operator=(const XamlObject &);
            int Column = 0;
            int Row = 0;
        };
    } // namespace Objects
} // namespace OpenXaml
