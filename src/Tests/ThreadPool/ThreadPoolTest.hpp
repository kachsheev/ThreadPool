#ifndef TESTS_THREADPOOL_THREADPOOLTEST_HPP
#define TESTS_THREADPOOL_THREADPOOLTEST_HPP

#include "Tests.hpp"
#include "../../Types.hpp"

class ThreadPoolTest: public TestAggregator
{
public:
	ThreadPoolTest();
	virtual ~ThreadPoolTest();

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
	QueueBuffer<TaskId, COUNT_TASKS> taskIds;
};

#endif // TESTS_THREADPOOL_THREADPOOLTEST_HPP
