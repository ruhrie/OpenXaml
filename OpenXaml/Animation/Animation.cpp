#include "OpenXaml/Animation/Animation.h"
#include "OpenXaml/Animation/AnimationEvent.h"
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <tuple>
#include <vector>
using namespace std::chrono;
namespace OpenXaml
{
    namespace Animation
    {
        //https://en.cppreference.com/w/cpp/thread/condition_variable
        std::priority_queue<AnimationEvent, std::vector<AnimationEvent>, std::greater<AnimationEvent>> waitQueue;
        std::condition_variable cv;
        std::mutex queueMutex, workerMutex, stopMutex;
        std::thread animationThread;
        bool stopThread = false;
        void AddTimeoutEvent(Objects::XamlObject *object, AnimationEvent event)
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
                else
                {
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
                            //notify here
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
    } // namespace Animation
} // namespace OpenXaml