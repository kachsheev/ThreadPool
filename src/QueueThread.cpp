#include "QueueThread.hpp"

QueueThread::QueueThread() : Thread(), uniqueId(0)
{
}

QueueThread::~QueueThread()
{
}

TaskId QueueThread::pushTask(AbstractTask &task)
{
	TaskId taskId(uniqueId, &task, this);
	info.processingTasks.push(&task);

	++uniqueId;

	return taskId;
}

void QueueThread::run()
{
	static const types::Size MAX_COUNT_ITERATIONS_WAITING = 50;
	Mutex internalMutex;
	types::Size counter;
	info.internal = &internalMutex;
	while(!info.join->tryWait())
	{
		info.status = Status::READY;
		if (info.processingTasks.size())
		{
			info.status = Status::PERFOMING;

			internalMutex.lock();
			(*info.processingTasks.head())();
			internalMutex.unlock();

			info.finishedTasks.push(info.processingTasks.pop());
		}
		else
		{
			if (counter < MAX_COUNT_ITERATIONS_WAITING)
			{
				++counter;
			}
			else
			{
				// sleep
				internalMutex.lock();
			}
		}
	}
	info.status = Status::FINISHED;
}
