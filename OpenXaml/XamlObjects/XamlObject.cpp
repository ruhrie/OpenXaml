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
            this->minCoord = coordinate{0, 0};
            this->maxCoord = coordinate{0, 0};
            maxRendered = {0.0f, 0.0f};
            minRendered = {0.0f, 0.0f};
            this->Visibility = OpenXaml::Visibliity::Visible;
        }

        void XamlObject::SetBoundingBox(coordinate min, coordinate max)
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
            for (auto child : Children)
            {
                delete child;
            }
            for (auto der : DerivedElements)
            {
                delete der;
            }
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

        coordinate XamlObject::GetMaxRendered()
        {
            coordinate result = {-1.0f, -1.0f};
            for (auto der : DerivedElements)
            {
                result.x = std::max(result.x, der->maxRendered.x);
                result.y = std::max(result.y, der->maxRendered.y);
            }
            result.x = std::max(result.x, maxRendered.x);
            result.y = std::max(result.y, maxRendered.y);
            return result;
        }

        coordinate XamlObject::GetMinRendered()
        {
            coordinate result = {1.0f, 1.0f};
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

        void XamlObject::setVisibility(OpenXaml::Visibliity vis)
        {
            Visibility = vis;
        }

        OpenXaml::Visibliity XamlObject::getVisibility()
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
            float xc = (float)x * OpenXaml::Environment::window->xScale - 1.0f;
            float yc = 1.0f - (float)y * OpenXaml::Environment::window->yScale;
            if (xc > minRendered.x && xc < maxRendered.x)
            {
                if (yc < maxRendered.y && yc > minRendered.y)
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
