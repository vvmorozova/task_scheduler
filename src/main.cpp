#include "task_scheduler.h"
#include <iostream>

void func()
{
    std::cout << "it s me func" << std::endl;
}
int main()
{
    TaskScheduler Scheduler1;
    std::time_t time1 = time(0) + 4, time2 = time(0) + 1, time3 = time(0) + 7, currTime = time(0);
    Scheduler1.Add(func, time1);
    Scheduler1.Add(func, time2);
    Scheduler1.Add([]{std::cout << "third func" << std::endl;}, time3);
    std::cout << "curr time " << ctime(&currTime) << std::endl;
    Scheduler1.waitAllTasks();

    return 0;
}