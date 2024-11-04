#pragma once

#include <chrono>
#include <functional>
class TaskScheduler
{
private:
public:
    TaskScheduler();
    ~TaskScheduler();
    void Add(std::function task, std::time_t timestamp);
};
