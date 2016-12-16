#include <cassert>
#include "Templates/RwLockQueueBuffer.hpp"
#include "ThreadPool.hpp"

struct ThreadPool::ProcessingTasks:
		public RwLockQueueBuffer<AbstractTask *,
				ThreadPool::BUFFER_PROCESSING_TASKS_SIZE>
{
};

struct ThreadPool::FinishedTasks:
		public RwLockQueueBuffer<AbstractTask *,
				ThreadPool::BUFFER_FINISHED_TASKS_SIZE>
{
};

void ThreadPool::Thread::run()
{
	static const types::Size MAX_COUNT_ITERATIONS_WAITING = 50;
	Mutex internalMutex;
	types::Size counter;
	id.internal = &internalMutex;
	while(!id.join->tryWait())
	{
		id.status = ThreadPool::ThreadStatus::READY;
		if (id.processingTasks->size())
		{
			id.status = ThreadPool::ThreadStatus::PERFOMING;

			internalMutex.lock();
			(*id.processingTasks->head())();
			internalMutex.unlock();

			id.finishedTasks->push(id.processingTasks->pop());
		}
		else
		{
			if (counter < MAX_COUNT_ITERATIONS_WAITING)
			{
				++counter;
			}
			else
			{
				// sleep
				internalMutex.lock();
			}
		}
	}
	id.status = ThreadPool::ThreadStatus::FINISHED;
}

ThreadPool::ThreadPool() :
		lastId(0),
		lastIdSemaphore(1),
		threadCapacity(0),
		arrayThread(nullptr),
		blockedSemaphores(nullptr),
		processingTasks(nullptr),
		finishedTasks(nullptr)
{
}

ThreadPool::ThreadPool(types::Size countThreads) : ThreadPool()
{
	init(countThreads);
}

ThreadPool::~ThreadPool()
{
	clear();
}

ThreadPool::TaskId ThreadPool::addTask(AbstractTask &task)
{
	using Size = types::Size;

	types::Size countTasks = BUFFER_PROCESSING_TASKS_SIZE;
	types::Size queueNumber = 0;
	for (Size i = 0; i < threadCapacity; ++i)
	{
		if (processingTasks[i].size() < countTasks) {
			countTasks = processingTasks[i].size();
			queueNumber = i;
		}
	}

	return addTask(queueNumber, task);
}

ThreadPool::TaskId ThreadPool::addTask(types::Size queueNumber, AbstractTask &task)
{
	TaskId taskId;
	if (queueNumber < threadCapacity)
	{
		processingTasks[queueNumber].push(&task);

		lastIdSemaphore.wait();
		taskId.id = lastId++;
		lastIdSemaphore.post();

		taskId.threadIndex = queueNumber;
		taskId.task = &task;
		taskId.pool = this;
	}

	return taskId;
}

ThreadPool::TaskStatus ThreadPool::getTaskStatus(const TaskId &taskId) const
{
	using Size = types::Size;

	if (taskId.pool && taskId.task && taskId.threadIndex < threadCapacity)
	{
		ProcessingTasks &processing = *(arrayThread[taskId.threadIndex].id.processingTasks);
		for (Size i = 0; i < processing.size(); ++i)
		{
			if (taskId.task == processing[i])
			{
				if (i == 0)
				{
					return TaskStatus::PROCESS;
				}
				else
				{
					return TaskStatus::QUEUED;
				}
			}
		}

		FinishedTasks &finished = *(arrayThread[taskId.threadIndex].id.finishedTasks);
		for (Size i = 0; i < finished.size(); ++i)
		{
			if (taskId.task == finished[i])
			{
				return TaskStatus::FINISHED;
			}
		}
	}
	else
	{
		return TaskStatus::ERROR;
	}

	return TaskStatus::MISSED;
}

void ThreadPool::setCountThreads(types::Size countThreads)
{
	assert(threadCapacity != 0);
	init(countThreads);
}

void ThreadPool::start()
{
	using Size = types::Size;

	for (Size i = 0; i != threadCapacity; ++i)
	{
		arrayThread->start();
	}
}

void ThreadPool::stop()
{
	using Size = types::Size;

	for (Size i = 0; i < threadCapacity; ++i)
	{
		arrayThread[i].id.join->post();
		arrayThread[i].join();
	}
}

void ThreadPool::init(types::Size countThreads)
{
	using Size = types::Size;

	threadCapacity = countThreads;
	arrayThread = new Thread[countThreads];
	blockedSemaphores = new Semaphore[countThreads];
	processingTasks = new ProcessingTasks[countThreads];
	finishedTasks = new FinishedTasks[countThreads];

	for (Size i = 0; i < threadCapacity; ++i)
	{
		blockedSemaphores[i].post();
		arrayThread[i].id.join = blockedSemaphores + i;
		arrayThread[i].id.parent = this;
		arrayThread[i].id.processingTasks = processingTasks + i;
		arrayThread[i].id.finishedTasks = finishedTasks + i;
	}
}

void ThreadPool::clear()
{
	stop();

	delete[] finishedTasks;
	delete[] processingTasks;
	delete[] blockedSemaphores;
	delete[] arrayThread;
}
