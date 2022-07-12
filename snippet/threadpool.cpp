#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <iostream>
// #include <vector>
#include <chrono>

struct Task
{
    Task(int i)
    {
        idx=i;
    }
    void operator()()
    {
        std::cout << "hello " << idx << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "world " << idx << std::endl;
    }
    int idx;
};

class ThreadPool
{
public:
    ThreadPool(int size);
    void AddTask(Task &newTask);
    ~ThreadPool();
private:
    bool stop;
    std::mutex mtx;
    std::condition_variable cond;
    std::queue<Task> taskQueue;
    std::vector<std::thread> threads;
};

ThreadPool::ThreadPool(int size)
{
    stop=false;
    auto func=[this](){
        for(;;)
        {
            std::unique_lock<std::mutex> lock(mtx);
            cond.wait(lock, [this](){
                return stop || !taskQueue.empty();
            });
            if(stop && taskQueue.empty()) return;
            Task task=std::move(taskQueue.front());
            taskQueue.pop();
            lock.unlock();
            task();
        }
    };
    for(int i=0;i<size;++i)
    {
        threads.emplace_back(std::thread(func));
    }
}

void ThreadPool::AddTask(Task &newTask)
{
    if(stop) return;
    std::unique_lock<std::mutex> lock(mtx);
    taskQueue.emplace(newTask);
    lock.unlock();
    cond.notify_one();
}

ThreadPool::~ThreadPool()
{
    std::unique_lock<std::mutex> lock(mtx);
    stop=true;
    lock.unlock();
    cond.notify_all();
    for(auto &t:threads)
    {
        t.join();
    }
}

int main()
{
    ThreadPool pool(4);
    for(int i=0;i<8;++i)
    {
        Task t;
        pool.AddTask(t);
    }

    return 0;
}
