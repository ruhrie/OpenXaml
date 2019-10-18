#include "OpenXaml/Animation/Animation.h"
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
namespace OpenXaml
{
    namespace Animation
    {
        //https://en.cppreference.com/w/cpp/thread/condition_variable
        std::priority_queue<std::chrono::steady_clock::time_point, std::vector<std::chrono::steady_clock::time_point>, std::greater<std::chrono::steady_clock::time_point>> waitQueue;
        std::mutex m;
        void AddTimeoutEvent(Objects::XamlObject *object, std::chrono::duration<float> delay)
        {
            std::unique_lock<std::mutex> lk(m);
            //std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now() + delay;
            //waitQueue.push(time);
            lk.unlock();
            throw 2; //not implemented
        }
        //need to add worker thread and a method of starting it
    } // namespace Animation
} // namespace OpenXaml