#include <chrono>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

int thread_count = 0;
bool time_to_quit = false;
std::mutex m;
std::condition_variable cv;

void f(int id)
{
    {
    std::lock_guard<std::mutex> _(m);
    ++thread_count;
    }
    while (true)
    {
        {
        std::lock_guard<std::mutex> _(m);
        std::cout << "thread " << id << " working\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        std::lock_guard<std::mutex> _(m);
        if (time_to_quit)
            break;
    }
    std::lock_guard<std::mutex> _(m);
    std::cout << "thread ended\n";
    --thread_count;
    cv.notify_all();
}

int main()
{
    typedef std::chrono::steady_clock Clock;
    std::thread(f, 1).detach();
    std::thread(f, 2).detach();
    std::thread(f, 3).detach();
    std::thread(f, 4).detach();
    std::thread(f, 5).detach();
    auto t0 = Clock::now();
    auto t1 = t0 + std::chrono::seconds(5);
    std::unique_lock<std::mutex> lk(m);
    while (!time_to_quit && Clock::now() < t1)
        cv.wait_until(lk, t1);
    time_to_quit = true;
    std::cout << "main ending\n";
    while (thread_count > 0)
        cv.wait(lk);
    std::cout << "main ended\n";
}