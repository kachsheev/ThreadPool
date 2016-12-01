#include "QueueBufferTest.hpp"
#include "ThreadPoolTest.hpp"
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
	testThreadPool();
}

void AllTests::testQueueBuffer()
{
	QueueBufferTest queueBufferTest;
	queueBufferTest();
}

void AllTests::testThreadPool()
{
	ThreadPoolTest threadPoolTest;
	threadPoolTest();
}
