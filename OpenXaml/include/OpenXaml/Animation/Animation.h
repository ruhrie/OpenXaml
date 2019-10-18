#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
#include <chrono>
namespace OpenXaml
{
    namespace Animation
    {
        void AddTimeoutEvent(Objects::XamlObject *object, std::chrono::duration<float> delay);
    }
} // namespace OpenXaml