#ifndef TASKTHREAD_HPP
#define TASKTHREAD_HPP

#include "AbstractTask.hpp"
#include "Thread.hpp"
#include "Mutex.hpp"
#include "Templates/RwLockQueueBuffer.hpp"
#include "TaskId.hpp"

// TODO: написать тесты для потока с одной задачей
class TaskThread: public Thread
{
public:
	typedef Thread::Status Status;
	typedef types::TaskStatus TaskStatus;

	TaskThread();
	TaskThread(AbstractTask &task);
	virtual ~TaskThread();

	void addTask(AbstractTask &task);
	Status getStatus() const;
	TaskStatus getTaskStatus(const TaskId& taskId) const;

	Mutex &getRunMutex();
	Mutex &getSleepMutex();

protected:
	virtual void run();

private:
	TaskThread(const TaskThread &) = delete;
	TaskThread(TaskThread &&) = delete;
	TaskThread &operator=(const TaskThread &) = delete;
	TaskThread &operator=(TaskThread &&) = delete;

	AbstractTask *task;
	struct Info
	{
		Mutex mutexSleep;
		Mutex mutexRun;
		Status status;
	} info;
	RwLockQueueBuffer<AbstractTask *, 0ul> finishedTask;
};

#endif // TASKTHREAD_HPP
