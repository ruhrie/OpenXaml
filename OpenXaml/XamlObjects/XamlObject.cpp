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
#include <utility>

using namespace std;

namespace OpenXaml::Objects
{
    XamlObject::XamlObject()
    {
        this->Height = 0;
        this->Width = 0;
        this->VAO = 0;
        this->minCoord = vec2<float>{0, 0};
        this->maxCoord = vec2<float>{(float)Environment::window->width, (float)Environment::window->height};
        maxRendered = {0.0F, 0.0F};
        minRendered = {0.0F, 0.0F};
        this->Visibility = OpenXaml::Visibility::Visible;
    }

    void XamlObject::SetBoundingBox(vec2<float> min, vec2<float> max)
    {
        minCoord = min;
        maxCoord = max;
        for (const auto &child : Children)
        {
            child->SetBoundingBox(min, max);
        }
        for (const auto &der : DerivedElements)
        {
            der->SetBoundingBox(min, max);
        }
    }

    XamlObject::~XamlObject() = default;

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
    int XamlObject::getHeight() const
    {
        return this->Height;
    }
    void XamlObject::setWidth(int width)
    {
        this->Width = width;
    }
    int XamlObject::getWidth() const
    {
        return this->Width;
    }

    vec2<float> XamlObject::GetMaxRendered()
    {
        vec2<float> result = {FLT_MIN, FLT_MIN};
        for (const auto &der : DerivedElements)
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
        for (const auto &der : DerivedElements)
        {
            result.x = std::min(result.x, der->minRendered.x);
            result.y = std::min(result.y, der->minRendered.y);
        }
        result.x = std::min(result.x, minRendered.x);
        result.y = std::min(result.y, minRendered.y);
        return result;
    }

    int XamlObject::getColumn() const
    {
        return Column;
    }

    int XamlObject::getRow() const
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
        localMax.x = maxCoord.x - Margin.Right;
        localMax.y = maxCoord.y - Margin.Top;
        localMin.x = minCoord.x + Margin.Left;
        localMin.y = minCoord.y + Margin.Bottom;

        if (localMax.x < localMin.x)
        {
            localMax.x = localMin.x;
        }
        if (localMax.y < localMin.y)
        {
            localMax.y = localMin.y;
        }
    }

    void XamlObject::setOnClick(std::function<void(XamlObject *)> func)
    {

        if (OnClick != nullptr && func == nullptr)
        {
            Events::RemoveEvent(Events::XamlEvent::ClickEvent, this);
        }
        else if (OnClick == nullptr && func != nullptr)
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
        if (OnClick != nullptr)
        {
            OnClick(this);
        }
    }
    void XamlObject::Click(double x, double y)
    {
        float ny = Environment::window->height - y;
        if (x > minRendered.x && x < maxRendered.x)
        {
            if (ny < maxRendered.y && ny > minRendered.y)
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

    std::string XamlObject::getName()
    {
        return Name;
    }
    void XamlObject::setName(std::string name)
    {
        Name = std::move(name);
    }
} // namespace OpenXaml::Objects
