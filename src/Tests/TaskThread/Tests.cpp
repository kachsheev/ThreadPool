#include "Tests.hpp"

using namespace TaskThreadTests;

HelloWorldTask Constructor::hwTask;

int DefaultConstructor::runTest()
{
	return 0;
}

int Constructor::runTest()
{
	return 0;
}

int AddTask::runTest()
{
	if (taskThread.getStatus() == Thread::Status::READY)
	{
		std::cout << "TaskThread status is READY. Addidng task\n";

		taskThread.addTask(Constructor::hwTask);

		return 0;
	}
	else
	{

	}
	return 1;
}

int GetStatus::runTest()
{
	return 0;
}

int GetTaskStatus::runTest()
{
	return 0;
}
