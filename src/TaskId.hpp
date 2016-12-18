#ifndef TASKID_HPP
#define TASKID_HPP

#include "Types.hpp"
#include "AbstractTask.hpp"

class QueueThread;

class TaskId
{
public:
	TaskId() : id(0), task(nullptr), thread(nullptr)
	{
	}

	TaskId(TaskId &&taskId) : id(taskId.id),
			task(taskId.task), thread(taskId.thread)
	{
	}
	TaskId(const TaskId &taskId) : id(taskId.id),
			task(taskId.task), thread(taskId.thread)
	{
	}

	TaskId &operator=(const TaskId &taskId);
	TaskId &operator=(TaskId &&taskId);

	static const TaskId NULL_TASK_ID;

private:
	TaskId(types::Uint64 taskId,
			AbstractTask *thisTask, QueueThread *parentThread) :
			id(taskId), task(thisTask), thread(parentThread)
	{
	}

	types::Uint64 id;
	AbstractTask *task;
	QueueThread *thread;

	friend class ThreadPool;
	friend class QueueThread;
	friend bool operator ==(const TaskId& taskId1, const TaskId& taskId2);
	friend bool operator !=(const TaskId& taskId1, const TaskId& taskId2);
};

bool operator ==(const TaskId& taskId1,
		const TaskId& taskId2);
bool operator !=(const TaskId& taskId1,
		const TaskId& taskId2);

#endif // TASKID_HPP
