#ifndef TESTS_THREADPOOLTEST_HPP
#define TESTS_THREADPOOLTEST_HPP

#include "AbstractTest.hpp"
#include "../ThreadPool.hpp"

class ThreadPoolTest : public AbstractTest
{
public:
	ThreadPoolTest();
	virtual ~ThreadPoolTest();

	virtual void operator()();

private:
	enum Constants: types::Size
	{
		COUNT_THREADS = 2,
		COUNT_TASKS = 8
	};

	void constructors();
	void destrutor();

	void addTask();
	void getTaskStatus();
	void setCountThreads();

	void start();
	void stop();

	ThreadPool *pool;
	QueueBuffer<AbstractTask *, COUNT_TASKS> tasks;
	QueueBuffer<ThreadPool::TaskId, COUNT_TASKS> taskIds;
};

#endif // TESTS_THREADPOOLTEST_HPP
