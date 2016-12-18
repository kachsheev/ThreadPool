#include "TaskThread.hpp"

TaskThread::TaskThread() : task(nullptr)
{
}

TaskThread::TaskThread(AbstractTask &newTask) : task(&newTask)
{
}

TaskThread::~TaskThread()
{
}


