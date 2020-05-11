#pragma once
#include "OpenXaml/XamlEvents/XamlEvent.h"
namespace OpenXaml
{
    namespace Events
    {
        ///A key down event class
        class KeyDownEvent : public EventBase
        {
        public:
            KeyDownEvent();
        };
    } // namespace Events
} // namespace OpenXaml