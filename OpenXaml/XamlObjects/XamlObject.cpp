#include "OpenXaml/XamlObjects/XamlObject.h"
#include "OpenXaml/Properties/Alignment.h"
#include "OpenXaml/Properties/Visibility.h"
#include "OpenXaml/XamlObjects/Button.h"
#include "OpenXaml/XamlObjects/Rectangle.h"
#include "OpenXaml/XamlObjects/TextBlock.h"
#include <OpenXaml/Environment/Environment.h>
#include <OpenXaml/Environment/Window.h>
#include <OpenXaml/XamlEvents/XamlEvent.h>
#include <algorithm>
#include <cfloat>
#include <functional>

using namespace std;

namespace OpenXaml
{
    namespace Objects
    {
        XamlObject::XamlObject()
        {
            this->Height = 0;
            this->Width = 0;
            this->VAO = 0;
            this->minCoord = vec2<float>{0, 0};
            this->maxCoord = vec2<float>{(float)Environment::window->width, (float)Environment::window->height};
            maxRendered = {0.0f, 0.0f};
            minRendered = {0.0f, 0.0f};
            this->Visibility = OpenXaml::Visibility::Visible;
        }

        void XamlObject::SetBoundingBox(vec2<float> min, vec2<float> max)
        {
            minCoord = min;
            maxCoord = max;
            for (auto child : Children)
            {
                child->SetBoundingBox(min, max);
            }
            for (auto der : DerivedElements)
            {
                der->SetBoundingBox(min, max);
            }
        }

        XamlObject::~XamlObject()
        {
        }

        void XamlObject::setHorizontalAlignment(OpenXaml::HorizontalAlignment alignment)
        {
            this->HorizontalAlignment = alignment;
        }

        void XamlObject::setVerticalAlignment(OpenXaml::VerticalAlignment alignment)
        {
            this->VerticalAlignment = alignment;
        }

        HorizontalAlignment XamlObject::getHorizontalAlignment()
        {
            return this->HorizontalAlignment;
        }

        VerticalAlignment XamlObject::getVerticalAlignment()
        {
            return this->VerticalAlignment;
        }

        void XamlObject::setHeight(int height)
        {
            this->Height = height;
        }
        int XamlObject::getHeight()
        {
            return this->Height;
        }
        void XamlObject::setWidth(int width)
        {
            this->Width = width;
        }
        int XamlObject::getWidth()
        {
            return this->Width;
        }

        vec2<float> XamlObject::GetMaxRendered()
        {
            vec2<float> result = {FLT_MIN, FLT_MIN};
            for (auto der : DerivedElements)
            {
                result.x = std::max(result.x, der->maxRendered.x);
                result.y = std::max(result.y, der->maxRendered.y);
            }
            result.x = std::max(result.x, maxRendered.x);
            result.y = std::max(result.y, maxRendered.y);
            return result;
        }

        vec2<float> XamlObject::GetMinRendered()
        {
            vec2<float> result = {FLT_MAX, FLT_MAX};
            for (auto der : DerivedElements)
            {
                result.x = std::min(result.x, der->minRendered.x);
                result.y = std::min(result.y, der->minRendered.y);
            }
            result.x = std::min(result.x, minRendered.x);
            result.y = std::min(result.y, minRendered.y);
            return result;
        }

        int XamlObject::getColumn()
        {
            return Column;
        }

        int XamlObject::getRow()
        {
            return Row;
        }

        void XamlObject::setRow(int row)
        {
            Row = row;
        }

        void XamlObject::setColumn(int column)
        {
            Column = column;
        }

        void XamlObject::setVisibility(OpenXaml::Visibility vis)
        {
            Visibility = vis;
        }

        OpenXaml::Visibility XamlObject::getVisibility()
        {
            return XamlObject::Visibility;
        }

        void XamlObject::Update()
        {
            maxRendered = GetMaxRendered();
            minRendered = GetMinRendered();
        }

        void XamlObject::setOnClick(std::function<void(XamlObject *)> func)
        {

            if (OnClick != NULL && func == NULL)
            {
                Events::RemoveEvent(Events::XamlEvent::ClickEvent, this);
            }
            else if (OnClick == NULL && func != NULL)
            {
                Events::AddEvent(Events::XamlEvent::ClickEvent, this);
            }
            OnClick = func;
        }

        function<void(XamlObject *)> XamlObject::getOnClick()
        {
            return OnClick;
        }

        void XamlObject::Click()
        {
            if (OnClick != NULL)
            {
                OnClick(this);
            }
        }
        void XamlObject::Click(double x, double y)
        {
            if (x > minRendered.x && x < maxRendered.x)
            {
                if (y < maxRendered.y && y > minRendered.y)
                {
                    Environment::ActiveElement = this;
                    Click();
                }
            }
        }

        void XamlObject::AnimationUpdate(int arg)
        {
            Update();
        }
    } // namespace Objects
} // namespace OpenXaml
