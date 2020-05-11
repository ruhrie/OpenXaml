#include "OpenXaml/XamlEvents/TextEvent.h"

namespace OpenXaml
{
    namespace Events
    {
        TextEvent::TextEvent(std::string text)
        {
            eventType = XamlEvent::TextEvent;
            Text = text;
        }
    } // namespace Events
} // namespace OpenXaml
