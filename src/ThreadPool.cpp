#include "ThreadPool.hpp"

ThreadPool::ThreadPool()
{
}

ThreadPool::ThreadPool(types::Size countThreads) :
		queueThreads(countThreads),
		taskThreads(countThreads)
{
}

ThreadPool::~ThreadPool()
{
	for (types::Size i = 0; i != queueThreads.size(); ++i)
	{
		queueThreads[i]->join();
	}

	for (types::Size i = 0; i != taskThreads.size(); ++i)
	{
		taskThreads[i]->join();
	}
}

TaskId ThreadPool::addTask(AbstractTask &task)
{
	TaskId taskId;
	taskId.id = lastId++;
	taskId.task = &task;
	taskId.threadType = types::ThreadType::SIMPLE;

	return taskId;
}

TaskId ThreadPool::addTask(types::Size threadNumber, AbstractTask &task)
{
	TaskId taskId;
	taskId.id = lastId++;
	taskId.task = &task;
	taskId.threadType = types::ThreadType::QUEUE;

	return taskId;
}

ThreadPool::TaskStatus ThreadPool::getTaskStatus(const TaskId &taskId) const
{

}

void ThreadPool::start()
{

}

void ThreadPool::stop()
{

}

void ThreadPool::setCountTaskThreads(types::Size size)
{

}

types::Size ThreadPool::getCountTaskThreads() const noexcept
{
	return taskThreads.size();
}

void ThreadPool::setCountQueueThreads(types::Size size)
{

}

types::Size ThreadPool::getCountQueueThreads() const noexcept
{
	return queueThreads.size();
}

