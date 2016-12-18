#ifndef TASKTHREAD_HPP
#define TASKTHREAD_HPP

#include "AbstractTask.hpp"
#include "Thread.hpp"

class TaskThread: public Thread
{
public:
	typedef types::ThreadStatus Status;
	typedef types::TaskStatus TaskStatus;

	TaskThread();
	TaskThread(AbstractTask &task);
	virtual ~Thread();

	void addTask(AbstractTask &task);
	Status getStatus();
	TaskStatus getTaskStatus();

protected:
	virtual void run();

private:
	AbstractTask *task;
	struct Info
	{
		Status status;
		TaskStatus taskStatus;
	} info;
};

#endif // TASKTHREAD_HPP
