#pragma once
#include "OpenXaml/Animation/AnimationEvent.h"
#include "OpenXaml/XamlObjects/XamlObject.h"
#include <chrono>
namespace OpenXaml
{
    namespace Animation
    {
        void AddTimeoutEvent(AnimationEvent event);
        void StartAnimationThread();
        void StopAnimationThread();
        void PostPendingAnimations();
    } // namespace Animation
} // namespace OpenXaml