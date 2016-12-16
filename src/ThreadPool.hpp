#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <cstdint>

#include "Types.hpp"
#include "AbstractTask.hpp"
#include "Descriptor.hpp"
#include "Semaphore.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"
#include "Templates/QueueBuffer.hpp"

class ThreadPool
{
public:
	enum class TaskStatus
	{
		ERROR,
		MISSED,
		QUEUED,
		PROCESS,
		FINISHED
	};

	class TaskId;

	typedef void*(*ThreadTaskType)(void *);

	ThreadPool();
	ThreadPool(types::Size countThreads);
	~ThreadPool();

	ThreadPool(const ThreadPool &) = delete;
	ThreadPool(ThreadPool &&) = delete;
	ThreadPool &operator=(ThreadPool &&) = delete;
	ThreadPool &operator=(const ThreadPool &) = delete;

	TaskId addTask(AbstractTask &task);
	TaskId addTask(types::Size queueNumber, AbstractTask &task);
	TaskStatus getTaskStatus(const TaskId &taskId) const;

	void setCountThreads(types::Size size);

	void start();
	void stop();

	// future
	// bool stopThread(types::Size index);
	// bool startThread(types::Size index);

private:
	enum Constants: types::Size
	{
		BUFFER_PROCESSING_TASKS_SIZE = 64,
		BUFFER_FINISHED_TASKS_SIZE = 64
	};

	enum class ThreadStatus
	{
		NOT_RUN,
		STARTING,
		READY,
		PERFOMING,
		FINISHED
	};

	struct ProcessingTasks;
	struct FinishedTasks;

	class Thread: public ::Thread
	{
	protected:
		virtual void run();

		ThreadStatus getStatus();

	private:
		struct ThreadId
		{
			Descriptor descriptor;
			Semaphore *join;
			Mutex *internal;
			ThreadPool *parent;
			ProcessingTasks *processingTasks;
			FinishedTasks *finishedTasks;

			ThreadPool::ThreadStatus status;
		} id;

		friend class ThreadPool;
	};

	void init(types::Size countThreads);
	void clear();

	types::Size lastId;
	Semaphore lastIdSemaphore;

	types::Size threadCapacity;
	Thread *arrayThread;
	Semaphore *blockedSemaphores;
	ProcessingTasks *processingTasks;
	FinishedTasks *finishedTasks;
};

class ThreadPool::TaskId
{
public:
	TaskId() : id(0), threadIndex(0), task(nullptr), pool(nullptr)
	{
	}

	TaskId(ThreadPool::TaskId &&taskId) : id(taskId.id),
			threadIndex(taskId.threadIndex),
			task(taskId.task), pool(taskId.pool)
	{
	}
	TaskId(const ThreadPool::TaskId &taskId) : id(taskId.id),
			threadIndex(taskId.threadIndex),
			task(taskId.task), pool(taskId.pool)
	{
	}

	TaskId &operator=(const ThreadPool::TaskId &taskId);
	TaskId &operator=(ThreadPool::TaskId &&taskId);

private:
	TaskId(types::Uint64 taskId, types::Size taskThreadIndex,
			AbstractTask *thisTask, ThreadPool *parent) :
			id(taskId), threadIndex(taskThreadIndex), task(thisTask), pool(parent)
	{
	}

	types::Uint64 id;
	types::Size threadIndex;
	AbstractTask *task;
	ThreadPool *pool;

	friend class ThreadPool;
	friend bool operator ==(const TaskId& taskId1, const TaskId& taskId2);
	friend bool operator !=(const TaskId& taskId1, const TaskId& taskId2);
};

bool operator ==(const ThreadPool::TaskId& taskId1,
		const ThreadPool::TaskId& taskId2);
bool operator !=(const ThreadPool::TaskId& taskId1,
		const ThreadPool::TaskId& taskId2);

#endif // THREADPOOL_HPP
