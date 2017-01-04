#include "QueueBuffer/QueueBufferTest.hpp"
#include "TaskThread/TaskThreadTest.hpp"
#include "ThreadPool/ThreadPoolTest.hpp"
#include "AllTests.hpp"

AllTests::AllTests()
{
}

AllTests::~AllTests()
{
}

void AllTests::operator ()()
{
	testQueueBuffer();
	testTaskThread();
	testThreadPool();
}

void AllTests::testQueueBuffer()
{
	QueueBufferTest queueBufferTest;
	queueBufferTest.start();
}

void AllTests::testThreadPool()
{
//	ThreadPoolTest threadPoolTest;
//	threadPoolTest.start();
}

void AllTests::testTaskThread()
{
	TaskThreadTest taskThreadTest;
	taskThreadTest.start();
}
