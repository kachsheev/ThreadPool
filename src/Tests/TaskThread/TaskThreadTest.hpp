#ifndef TASKTHREADTEST_HPP
#define TASKTHREADTEST_HPP

#include "Tests.hpp"

class TaskThreadTest: public TestAggregator
{
public:
	TaskThreadTest();
	virtual ~TaskThreadTest();

private:
	using TestAggregator::pushBackTest;

	TaskThreadTests::DefaultConstructor defaultConstructor;

	TaskThreadTests::AddTask addTaskDefaultConstructor;
	TaskThreadTests::GetStatus getStatusDefaultConstructor;
	TaskThreadTests::GetTaskStatus getTaskStatusDefaultConstructor;

	TaskThreadTests::Constructor constructor;

	TaskThreadTests::AddTask addTaskConstructor;
	TaskThreadTests::GetStatus getStatusConstructor;
	TaskThreadTests::GetTaskStatus getTaskStatusConstructor;
};

#endif // TASKTHREADTEST_HPP
