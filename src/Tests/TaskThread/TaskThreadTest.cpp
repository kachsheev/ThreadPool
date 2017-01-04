#include "TaskThreadTest.hpp"

TaskThreadTest::TaskThreadTest() :
		defaultConstructor(),
		addTaskDefaultConstructor(defaultConstructor.getThread()),
		getStatusDefaultConstructor(defaultConstructor.getThread()),
		getTaskStatusDefaultConstructor(defaultConstructor.getThread()),
		constructor(),
		addTaskConstructor(constructor.getThread()),
		getStatusConstructor(constructor.getThread()),
		getTaskStatusConstructor(constructor.getThread())
{
	pushBackTest(&defaultConstructor);
	pushBackTest(&addTaskDefaultConstructor);
	pushBackTest(&getStatusDefaultConstructor);
	pushBackTest(&getTaskStatusDefaultConstructor);

	pushBackTest(&constructor);
//	pushBackTest(&addTaskConstructor);
	pushBackTest(&getStatusConstructor);
	pushBackTest(&getTaskStatusConstructor);
}

TaskThreadTest::~TaskThreadTest()
{
}
