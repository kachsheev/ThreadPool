#include "ThreadPoolTest.hpp"

class HelloTask: public AbstractTask
{
public:
	HelloTask(): finished(false)
	{
	}

	bool isFinished()
	{
		return finished;
	}

	virtual ~HelloTask()
	{
	}

protected:
	virtual void operator()()
	{
//		std::cout << "Hello!\n";
//		std::cout.flush();
		finished = true;
		return;
	}

private:
	bool finished;
};

ThreadPoolTest::ThreadPoolTest() : pool(nullptr)
{
}

ThreadPoolTest::~ThreadPoolTest()
{
}

void ThreadPoolTest::operator ()()
{
	// first
	constructors();

	addTask();
	getTaskStatus();

	start();
	getTaskStatus();

	stop();

	destrutor();

	// second
	constructors();
	setCountThreads();

	addTask();
	getTaskStatus();

	start();
	getTaskStatus();

	stop();

	destrutor();
}

void ThreadPoolTest::constructors()
{
	unsigned int counter = 0;
	if (counter == 0)
	{
		pool = new ThreadPool(COUNT_THREADS);
	}
	else if (counter == 1)
	{
		pool = new ThreadPool;
	}
	++counter;
}

void ThreadPoolTest::destrutor()
{
	delete pool;
	pool = nullptr;
}

void ThreadPoolTest::addTask()
{
	using Size = types::Size;
	using TaskId = ThreadPool::TaskId;

	for (Size i = 0; i < tasks.capacity(); ++i)
	{
		tasks.push(new HelloTask());

		AbstractTask &task = *tasks.tail();
		TaskId taskId = pool->addTask(task);
		taskIds.push(taskId);
	}
}

void ThreadPoolTest::getTaskStatus()
{
	using TaskStatus = ThreadPool::TaskStatus;
	using Size = types::Size;

	for (Size i = 0; i < taskIds.size(); ++i)
	{
		TaskStatus status = pool->getTaskStatus(taskIds[i]);
		switch (status)
		{
			case TaskStatus::MISSED:
			{
				std::cout << "Task " << i << " : " "MISSED";
				break;
			}
			case TaskStatus::QUEUED:
			{
				std::cout << "Task " << i << " : " "QUEUED";
				break;
			}
			case TaskStatus::PROCESS:
			{
				std::cout << "Task " << i << " : " "PROCESS";
				break;
			}
			case TaskStatus::FINISHED:
			{
				std::cout << "Task " << i << " : " "FINISHED";
				break;
			}
			default:
				break;
		}
		std::cout << '\n';
	}
}

void ThreadPoolTest::setCountThreads()
{
	pool->setCountThreads(COUNT_THREADS);
}

void ThreadPoolTest::start()
{
	pool->start();
}

void ThreadPoolTest::stop()
{
	using Size = types::Size;

	pool->stop();

	Size tasksSize = tasks.size();
	for (Size i = 0; i < tasksSize; ++i)
	{
		auto task = tasks.pop();
		delete task;
	}
}
