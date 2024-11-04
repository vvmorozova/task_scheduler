#include "task_scheduler.h"

void TaskScheduler::Add(std::function<void()> task, std::time_t timestamp)
{
    std::lock_guard<std::mutex> lock(mtx);
    taskQueue.emplace(std::move(task), timestamp);
    currentTasksNum++;
    waitCondition.notify_all();
}

void TaskScheduler::waitAllTasks()
{
    std::unique_lock<std::mutex> lock(this->mtx);
    waitCondition.wait(lock, [this]
                       { return this->currentTasksNum == 0; });
}

void TaskScheduler::runTasks()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        waitCondition.wait(lock, [this]
                           { return finishProgram || !taskQueue.empty(); });
        if (finishProgram)
            break;

        std::time_t now = std::time(0);

        if (taskQueue.empty() || taskQueue.top().second > now)
        {
            if (!taskQueue.empty())
                waitCondition.wait_until(lock, std::chrono::system_clock::from_time_t(taskQueue.top().second));
        }
        else
        {
            std::function<void()> currTask = taskQueue.top().first;

            taskQueue.pop();
            lock.unlock();
            currTask();
            currentTasksNum--;
        }
    }
}