#include "TaskThread.hpp"

TaskThread::TaskThread() : task(nullptr), finishedTask()
{
}

TaskThread::TaskThread(AbstractTask &newTask) : task(&newTask)
{
}

TaskThread::~TaskThread()
{
}

void TaskThread::addTask(AbstractTask &runnableTask)
{
	while (getStatus() != Thread::Status::READY);

	task = &runnableTask;

	getRunMutex().unlock();
}

Thread::Status TaskThread::getStatus() const
{
	return info.status;
}

TaskThread::TaskStatus TaskThread::getTaskStatus(const TaskId &taskId) const
{
	if (taskId.task == task)
	{
		return TaskStatus::PROCESS;
	}
	else
	{
		for (types::Size i = 0; i < finishedTask.size(); ++i)
		{
			if (taskId.task == finishedTask[i])
			{
				return TaskStatus::FINISHED;
			}
		}
	}
	return types::TaskStatus::MISSED;
}

void TaskThread::run()
{
	while (!info.mutexRun.tryLock())
	{
		info.mutexSleep.unlock();
		if (task)
		{
			info.status = Thread::Status::PERFOMING;
			(*task)();
			finishedTask.push(task);
			task = nullptr;
			info.status = Thread::Status::FINISHED;
		}
		info.mutexSleep.lock();
		info.status = Thread::Status::READY;
	}
}

Mutex &TaskThread::getRunMutex()
{
	return info.mutexRun;
}

Mutex &TaskThread::getSleepMutex()
{
	return info.mutexSleep;
}
