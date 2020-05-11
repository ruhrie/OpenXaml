#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
#include <chrono>
#include <math.h>
namespace OpenXaml
{
    namespace Animation
    {
        struct AnimationEvent
        {
            Objects::XamlObject *Target;
            std::chrono::steady_clock::time_point Time;
            int Argument;

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

            AnimationEvent(Objects::XamlObject *target, std::chrono::microseconds delay, int argument = -1)
            {
                Time = std::chrono::steady_clock::now() + delay;
                Target = target;
                Argument = argument;
            }
            AnimationEvent()
            {
                Time = std::chrono::steady_clock::now();
                Target = NULL;
                Argument = -1;
            }
        };
    } // namespace Animation
} // namespace OpenXaml
