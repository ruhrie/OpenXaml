#include "OpenXaml/Animation/Animation.h"
#include <GLFW/glfw3.h>
#include <condition_variable>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <tuple>
#include <vector>
using namespace std::chrono;
namespace OpenXaml::Animation
{
    //https://en.cppreference.com/w/cpp/thread/condition_variable
    std::priority_queue<AnimationEvent, std::vector<AnimationEvent>, std::greater<>> waitQueue;
    std::vector<AnimationEvent> AnimationQueue;
    std::condition_variable cv;
    std::mutex queueMutex, workerMutex, stopMutex, animationMutex;
    std::thread animationThread;
    bool stopThread = false;
    void AddTimeoutEvent(AnimationEvent event)
    {
        queueMutex.lock();
        waitQueue.push(event);
        queueMutex.unlock();
        cv.notify_one();
    }

    void AnimationWorker()
    {
        while (true)
        {
            stopMutex.lock();
            bool toStop = stopThread;
            stopMutex.unlock();
            bool toSkip = false;
            if (toStop)
            {
                return;
            }

            auto now = steady_clock::now();
            std::unique_lock<std::mutex> lk(queueMutex);
            AnimationEvent t;
            while (true)
            {
                if (waitQueue.empty())
                {
                    toSkip = true;
                    break;
                }
                t = waitQueue.top();
                if (t.Time <= now)
                {
                    waitQueue.pop();
                    animationMutex.lock();
                    AnimationQueue.push_back(t);
                    glfwPostEmptyEvent();
                    animationMutex.unlock();
                }
                else
                {
                    break;
                }
            }
            lk.unlock();
            std::unique_lock<std::mutex> pk(workerMutex);
            if (toSkip)
            {
                cv.wait(pk);
            }
            else
            {
                cv.wait_until(pk, t.Time);
            }
        }
    }
    void StartAnimationThread()
    {
        animationThread = std::thread(AnimationWorker);
    }
    void StopAnimationThread()
    {
        stopMutex.lock();
        stopThread = true;
        stopMutex.unlock();
        cv.notify_one();
        animationThread.join();
    }
    void GetPendingAnimations()
    {
        std::vector<AnimationEvent> pendingEvents;
        animationMutex.lock();
        pendingEvents = AnimationQueue;
        AnimationQueue.clear();
        animationMutex.unlock();
        for (auto event : pendingEvents)
        {
            event.Target->AnimationUpdate(event.Argument);
        }
    }
} // namespace OpenXaml::Animation