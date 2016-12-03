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

void *ThreadPool::taskFunc(void *data)
{
	ThreadPool::ThreadId *thread = reinterpret_cast<ThreadPool::ThreadId *>(data);
	Mutex internalMutex;
	thread->internal = &internalMutex;
	while(!thread->join->tryWait())
	{
		thread->status = ThreadPool::ThreadStatus::READY;
		while (thread->processingTasks->size())
		{
			thread->status = ThreadPool::ThreadStatus::PERFOMING;

			internalMutex.lock();
			(*thread->processingTasks->head())();
			internalMutex.unlock();

			thread->finishedTasks->push(thread->processingTasks->pop());
		}
	}
	thread->status = ThreadPool::ThreadStatus::FINISHED;
	return nullptr;
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
		ProcessingTasks &processing = *(arrayThread[taskId.threadIndex].processingTasks);
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

		FinishedTasks &finished = *(arrayThread[taskId.threadIndex].finishedTasks);
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

	for (Size i = threadCapacity; i != 0; --i)
	{
		createThread(arrayThread[threadCapacity - i], ThreadPool::taskFunc);
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
	arrayThread = new ThreadId[countThreads];
	blockedSemaphores = new Semaphore[countThreads];
	processingTasks = new ProcessingTasks[countThreads];
	finishedTasks = new FinishedTasks[countThreads];

	for (Size i = 0; i < threadCapacity; ++i)
	{
		blockedSemaphores[i].post();
		arrayThread[i].join = blockedSemaphores + i;
		arrayThread[i].parent = this;
		arrayThread[i].processingTasks = processingTasks + i;
		arrayThread[i].finishedTasks = finishedTasks + i;
	}
}

void ThreadPool::createThread(ThreadPool::ThreadId &thread,
		ThreadPool::ThreadTaskType threadTask)
{
	pthread_create(&thread.descriptor.get(),
			&thread.descriptor.attributes(),
			threadTask,
			reinterpret_cast<void *>(&thread));
}

void ThreadPool::clear()
{
	stop();

	delete[] finishedTasks;
	delete[] processingTasks;
	delete[] blockedSemaphores;
	delete[] arrayThread;
}

void ThreadPool::joinThread(ThreadId &thread)
{
	thread.join->post();
	pthread_join(thread.descriptor.get(), nullptr);
}
