#ifndef TESTS_QUEUEBUFFER_QUEUEBUFFERTEST_HPP
#define TESTS_QUEUEBUFFER_QUEUEBUFFERTEST_HPP

#include <cstdint>

#include "../../Templates/QueueBuffer.hpp"
#include "../Test.hpp"
#include "Tests.hpp"

class QueueBufferTest: public TestAggregator
{
public:
	QueueBufferTest() :
			push(queue),
			pop(queue),
			head(queue),
			tail(queue)
	{
		this->pushBackTest(&push);
		this->pushBackTest(&pop);
		this->pushBackTest(&head);
		this->pushBackTest(&tail);
	}

	virtual ~QueueBufferTest();

private:
	using TestAggregator::pushBackTest;

	QueueBufferTests::Push<long, 8ul> push;
	QueueBufferTests::Pop<long, 8ul> pop;
	QueueBufferTests::Head<long, 8ul> head;
	QueueBufferTests::Tail<long, 8ul> tail;

	QueueBuffer<long, 8ul> queue;
};

#endif // TESTS_QUEUEBUFFER_QUEUEBUFFERTEST_HPP
