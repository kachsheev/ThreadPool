#include "ThreadPool.hpp"

ThreadPool::TaskId &ThreadPool::TaskId::operator =(const ThreadPool::TaskId &taskId)
{
	id = taskId.id;
	threadIndex = taskId.threadIndex;
	task = taskId.task;
	pool = taskId.pool;
	return *this;
}

ThreadPool::TaskId &ThreadPool::TaskId::operator =(ThreadPool::TaskId &&taskId)
{
	id = taskId.id;
	threadIndex = taskId.threadIndex;
	task = taskId.task;
	pool = taskId.pool;
	return *this;
}

bool operator==(const ThreadPool::TaskId &taskId1, const ThreadPool::TaskId &taskId2)
{
	if (taskId1.pool == taskId2.pool
			&& taskId1.task == taskId2.task
			&& taskId1.id == taskId2.id
			&& taskId1.threadIndex == taskId2.threadIndex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator!=(const ThreadPool::TaskId &taskId1, const ThreadPool::TaskId &taskId2)
{
	if (taskId1.pool != taskId2.pool
			|| taskId1.task != taskId2.task
			|| taskId1.id != taskId2.id
			|| taskId1.threadIndex != taskId2.threadIndex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

