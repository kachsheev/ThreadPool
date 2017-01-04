#include "TaskId.hpp"

TaskId &TaskId::operator=(const TaskId &taskId)
{
	id = taskId.id;
	task = taskId.task;
	thread = taskId.thread;
	threadType = taskId.threadType;

	return *this;
}

TaskId &TaskId::operator=(TaskId &&taskId)
{
	id = taskId.id;
	task = taskId.task;
	thread = taskId.thread;
	threadType = taskId.threadType;

	return *this;
}

bool operator==(const TaskId &taskId1, const TaskId &taskId2)
{
	if (taskId1.threadType == taskId2.threadType
			&& taskId1.thread == taskId2.thread
			&& taskId1.task == taskId2.task
			&& taskId1.id == taskId2.id)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator!=(const TaskId &taskId1, const TaskId &taskId2)
{
	if (taskId1.threadType == taskId2.threadType
			|| taskId1.thread != taskId2.thread
			|| taskId1.task != taskId2.task
			|| taskId1.id != taskId2.id)
	{
		return true;
	}
	else
	{
		return false;
	}
}

