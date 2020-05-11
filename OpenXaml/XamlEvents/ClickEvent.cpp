#include "OpenXaml/XamlEvents/ClickEvent.h"

namespace OpenXaml::Events
{
    ClickEvent::ClickEvent(double x, double y)
    {
        eventType = XamlEvent::ClickEvent;
        xCoord = (float)x;
        yCoord = (float)y;
    }

    vec2<float> ClickEvent::GetLocation()
    {
        return vec2<float>{xCoord, yCoord};
    }
} // namespace OpenXaml::Events
