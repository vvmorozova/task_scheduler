#pragma once

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <iostream>

class TaskScheduler
{
public:
    TaskScheduler() : finishProgram(false), currentTasksNum(0) 
    {
        thread = std::thread([this]
                             { this->runTasks(); });
    };
    ~TaskScheduler() {
        std::lock_guard<std::mutex> lock(mtx);
        finishProgram = true;
        waitCondition.notify_all();
        thread.join();

    };
    /*
    The function prototype looks like this
    Add(std::function task, std::time_t timestamp)
    so I suppose that task doesn't have args and has void type
    */

    void Add(std::function<void()> task, std::time_t timestamp);

    void waitAllTasks();

private:
    using TaskType = std::pair<std::function<void()>, std::time_t>;

    class ComparePriorities
    {
    public:
        bool operator()(const TaskType &first, const TaskType &last)
        {
            return first.second > last.second;
        }
    };

    std::priority_queue<TaskType, std::vector<TaskType>, ComparePriorities> taskQueue;
    std::condition_variable waitCondition;
    std::mutex mtx;
    int currentTasksNum;
    std::thread thread;
    bool finishProgram;

    void runTasks();
};
