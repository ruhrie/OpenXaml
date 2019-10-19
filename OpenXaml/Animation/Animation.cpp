#include "OpenXaml/Animation/Animation.h"
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
using namespace std::chrono;
namespace OpenXaml
{
    namespace Animation
    {
        //https://en.cppreference.com/w/cpp/thread/condition_variable
        std::priority_queue<steady_clock::time_point, std::vector<steady_clock::time_point>, std::greater<steady_clock::time_point>> waitQueue;
        std::condition_variable cv;
        std::mutex queueMutex, workerMutex, stopMutex;
        std::thread animationThread;
        bool stopThread = false;
        void AddTimeoutEvent(Objects::XamlObject *object, microseconds delay)
        {
            queueMutex.lock();
            time_point<steady_clock> time = steady_clock::now() + delay;
            waitQueue.push(time);
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
                if (toStop)
                {
                    return;
                }
                else
                {
                    auto now = steady_clock::now();
                    steady_clock::time_point waitTil;
                    std::unique_lock<std::mutex> lk(queueMutex);
                    if (!waitQueue.empty())
                    {
                        auto t = waitQueue.top();
                        while (t <= now)
                        {
                            //notify controls here
                            waitQueue.pop();
                            if (waitQueue.empty())
                            {
                                t = now;
                                break;
                            }
                            t = waitQueue.top();
                        }
                        if (t != now)
                        {
                            waitTil = t;
                        }
                        else
                        {
                            waitTil = now;
                        }
                    }
                    else
                    {
                        waitTil = now;
                    }
                    lk.unlock();
                    std::unique_lock<std::mutex> pk(workerMutex);
                    if (waitTil == now)
                    {
                        cv.wait(pk);
                    }
                    else
                    {
                        cv.wait_until(pk, waitTil);
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