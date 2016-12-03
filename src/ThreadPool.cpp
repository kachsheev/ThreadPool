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

	static Size lastId = 0;
	static Semaphore semaphore(1);

	TaskId taskId;
	types::Size countTasks = BUFFER_PROCESSING_TASKS_SIZE;
	ProcessingTasks *needTaskBuffer = nullptr;
	for (Size i = 0; i < threadCapacity; ++i)
	{
		if (processingTasks[i].size() < countTasks) {
			countTasks = processingTasks[i].size();
			needTaskBuffer = &processingTasks[i];
		}
	}

	if (needTaskBuffer)
	{
		needTaskBuffer->push(&task);

		semaphore.wait();
		taskId.id = lastId++;
		semaphore.post();

		taskId.threadIndex = needTaskBuffer - processingTasks;
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
		arrayThread->run();
	}
}

void ThreadPool::stop()
{
	using Size = types::Size;

	for (Size i = 0; i < threadCapacity; ++i)
	{
		joinThread(arrayThread[i]);
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

void ThreadPool::joinThread(Thread &thread)
{
	thread.id.join->post();
	thread.join();
}
