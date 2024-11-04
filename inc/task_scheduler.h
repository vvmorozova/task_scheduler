#pragma once

#include <chrono>
#include <functional>
#include <queue>

class TaskScheduler
{
public:
    TaskScheduler() {};
    ~TaskScheduler() = default;
    /*
    The function prototype looks like this
    Add(std::function task, std::time_t timestamp)
    so I suppose that task doesn't have args and has void type
    */

    void Add(std::function<void()> task, std::time_t timestamp);

private:
    using TaskType = std::pair<std::time_t, std::function<void()>>;

    class ComparePriorities
    {
    public:
        bool operator()(const TaskType &first, const TaskType &last)
        {
            return first.first > last.first;
        }
    };

    std::priority_queue<TaskType, std::vector<TaskType>, ComparePriorities> taskQueue;
};
