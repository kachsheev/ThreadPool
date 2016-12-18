#ifndef QUEUETHREAD_HPP
#define QUEUETHREAD_HPP

#include "Templates/RwLockQueueBuffer.hpp"
#include "AbstractTask.hpp"
#include "TaskId.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"

class QueueThread: public Thread
{
public:
	typedef types::ThreadStatus Status;
	typedef types::TaskStatus TaskStatus;

	QueueThread();
	virtual ~QueueThread();

	TaskId pushTask(AbstractTask &task);
	TaskStatus getTaskStatus(const TaskId &taskId);
	AbstractTask &getTask(const TaskId &taskId);

protected:
	virtual void run();

private:
	types::Uint64 uniqueId;
	struct Info
	{
		Descriptor descriptor;
		Semaphore *join;
		Mutex *internal;
		Status status;
		RwLockQueueBuffer<AbstractTask *, 0ul> processingTasks;
		RwLockQueueBuffer<AbstractTask *, 0ul> finishedTasks;
	} info;

	friend class ThreadPool;
};

#endif // QUEUETHREAD_HPP
