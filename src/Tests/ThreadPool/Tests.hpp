#ifndef TESTS_THREADPOOL_TESTS_HPP
#define TESTS_THREADPOOL_TESTS_HPP

#include "../../ThreadPool.hpp"
#include "../Test.hpp"

// Task
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
		std::cout << "Hello!\n";
		std::cout.flush();
		finished = true;
		return;
	}

private:
	bool finished;
};

namespace ThreadPoolTests
{

class DefaultConstructor: public AbstractTest
{
public:
	DefaultConstructor()
	{
	}

	virtual ~DefaultConstructor()
	{
	}

	ThreadPool &getThreadPool()
	{
		return *pool;
	}

private:
	virtual int runTest();

	ThreadPool *pool;
};

class Destructor: public AbstractTest
{
public:
	Destructor(ThreadPool *dynamicPool) : pool(dynamicPool)
	{
	}

	virtual ~Destructor()
	{
	}

private:
	virtual int runTest();

	ThreadPool *pool;
};

class AddTask: public AbstractTest
{
public:
	AddTask(ThreadPool &refPool) : pool(refPool)
	{
	}

	virtual ~AddTask()
	{
	}

private:
	virtual int runTest();

	enum Constants: types::Size
	{
		COUNT_THREADS = 2,
		COUNT_TASKS = 8
	};

	ThreadPool &pool;
	QueueBuffer<AbstractTask *, COUNT_TASKS> tasks;
	QueueBuffer<TaskId, COUNT_TASKS> taskIds;
};

class GetTaskStatus: public AbstractTest
{
public:
	GetTaskStatus(ThreadPool &refPool) : pool(refPool)
	{
	}

	virtual ~GetTaskStatus()
	{
	}

private:
	virtual int runTest();

	ThreadPool &pool;
};

class SetCountThreads
{
public:
	SetCountThreads(ThreadPool &refPool) : pool(refPool)
	{
	}

	virtual ~SetCountThreads()
	{
	}

private:
	virtual int runTest();

	ThreadPool &pool;
};

class Start: public AbstractTest
{
public:
	Start(ThreadPool &refPool) : pool(refPool)
	{
	}

	virtual ~Start()
	{
	}

private:
	virtual int runTest();

	ThreadPool &pool;
};

class Stop: public AbstractTest
{
public:
	Stop(ThreadPool &refPool) : pool(refPool)
	{
	}

	virtual ~Stop()
	{
	}

private:
	virtual int runTest();

	ThreadPool &pool;
};

}

#endif // TESTS_THREADPOOL_TESTS_HPP
