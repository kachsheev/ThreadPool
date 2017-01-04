#include <iostream>
#include "../../Types.hpp"
#include "Tests.hpp"

using namespace std;

int ThreadPoolTests::DefaultConstructor::runTest()
{
	pool = new ThreadPool;
	return 0;
}

int ThreadPoolTests::Destructor::runTest()
{
	delete pool;
	return 0;
}

int ThreadPoolTests::AddTask::runTest()
{
	using Size = types::Size;

	for (Size i = 0; i < tasks.capacity(); ++i)
	{
		tasks.push(new HelloTask());

		AbstractTask &task = *tasks.tail();
		TaskId taskId = pool.addTask(task);
		taskIds.push(taskId);
	}
	return 0;
}

int ThreadPoolTests::GetTaskStatus::runTest()
{
	return 1;
}

int ThreadPoolTests::SetCountThreads::runTest()
{
	return 1;
}

int ThreadPoolTests::Start::runTest()
{
	this->pool.start();
	return 1;
}

int ThreadPoolTests::Stop::runTest()
{
	this->pool.stop();
	return 0;
}

