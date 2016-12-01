#ifndef QUEUEBUFFERTEST_HPP
#define QUEUEBUFFERTEST_HPP

#include <cstdint>

#include "../Templates/QueueBuffer.hpp"
#include "AbstractTest.hpp"

class QueueBufferTest: public AbstractTest
{
public:
	QueueBufferTest();
	virtual ~QueueBufferTest();

	virtual void operator()();

private:
	void push();
	void pop();

	void tail();
	void head();

	template<typename ArrayType>
	bool operatorIndex(const ArrayType *validArray, std::size_t arraySize)
	{
		bool valid = true;

		if (queue.size() == arraySize)
		{
			for (size_t i = 0; i < arraySize; ++i)
			{
				if (queue[i] != validArray[i])
				{
					valid = false;
				}
			}
		}
		else
		{
			valid = false;
		}

		isValid(valid);
		return valid;
	}

	QueueBuffer<int, 8u> queue;
	size_t count;
};

#endif // QUEUEBUFFERTEST_HPP
