#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include "Types.hpp"
#include "AbstractTask.hpp"
#include "Descriptor.hpp"
#include "Semaphore.hpp"
#include "Mutex.hpp"
#include "QueueThread.hpp"
#include "TaskThread.hpp"
#include "Templates/UniquePointer.hpp"

class TaskId;

class ThreadPool
{
public:
	typedef QueueThread::TaskStatus TaskStatus;
	typedef void*(*ThreadTaskType)(void *);

	ThreadPool();
	ThreadPool(types::Size countThreads);
	~ThreadPool();

	ThreadPool(const ThreadPool &) = delete;
	ThreadPool(ThreadPool &&) = delete;
	ThreadPool &operator=(ThreadPool &&) = delete;
	ThreadPool &operator=(const ThreadPool &) = delete;

	TaskId addTask(AbstractTask &task);
	TaskId addTask(types::Size threadNumber, AbstractTask &task);

	TaskStatus getTaskStatus(const TaskId &taskId) const;

	void setCountTaskThreads(types::Size size);
	types::Size getCountTaskThreads() const noexcept;

	void setCountQueueThreads(types::Size size);
	types::Size getCountQueueThreads() const noexcept;

	void start();
	void stop();

private:
	void init(types::Size countThreads);
	void clear();

	types::Uint64 lastId;
	QueueBuffer<UniquePointer<QueueThread>, 0ul> queueThreads;
	QueueBuffer<UniquePointer<TaskThread>, 0ul> taskThreads;
};

#endif // THREADPOOL_HPP
