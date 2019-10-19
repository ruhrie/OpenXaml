#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
#include <math.h>
#include <chrono>
namespace OpenXaml
{
    namespace Animation
    {
        struct AnimationEvent
        {
            Objects::XamlObject *Target;
            std::chrono::steady_clock::time_point Time;

            friend bool operator<(const AnimationEvent &lhs, const AnimationEvent &rhs)
            {
                return lhs.Time < rhs.Time;
            }
            friend bool operator>(const AnimationEvent &lhs, const AnimationEvent &rhs)
            {
                return lhs.Time > rhs.Time;
            }
            friend bool operator<=(const AnimationEvent &lhs, const AnimationEvent &rhs)
            {
                return lhs.Time <= rhs.Time;
            }
            friend bool operator>=(const AnimationEvent &lhs, const AnimationEvent &rhs)
            {
                return lhs.Time >= rhs.Time;
            }

            AnimationEvent(Objects::XamlObject *target, std::chrono::microseconds delay)
            {
                Time = std::chrono::steady_clock::now() + delay;
                Target = target;
            }
            AnimationEvent()
            {
                Time = std::chrono::steady_clock::now();
                Target = NULL;
            }
        };
    } // namespace Animation
} // namespace OpenXaml
