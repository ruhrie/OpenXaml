#include "OpenXaml/XamlEvents/TextEvent.h"

#include <utility>

namespace OpenXaml::Events
{
    TextEvent::TextEvent(std::string text)
    {
        eventType = XamlEvent::TextEvent;
        Text = std::move(text);
    }
} // namespace OpenXaml::Events
