#ifndef TASKID_HPP
#define TASKID_HPP

#include "Types.hpp"
#include "AbstractTask.hpp"
#include "Thread.hpp"

class QueueThread;

class TaskId
{
public:
	typedef types::ThreadType ThreadType;

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
			AbstractTask *thisTask, Thread *parentThread) :
			id(taskId), task(thisTask), thread(parentThread)
	{
	}

	types::Uint64 id;
	AbstractTask *task;
	Thread *thread;
	ThreadType threadType;

	friend bool operator==(const TaskId& taskId1,
			const TaskId& taskId2);
	friend bool operator!=(const TaskId& taskId1,
			const TaskId& taskId2);

	friend class ThreadPool;
	friend class QueueThread;
	friend class TaskThread;
};

bool operator==(const TaskId& taskId1,
		const TaskId& taskId2);
bool operator!=(const TaskId& taskId1,
		const TaskId& taskId2);

#endif // TASKID_HPP
