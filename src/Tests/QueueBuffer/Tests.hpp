#ifndef TESTS_QUEUEBUFFER_TESTS_HPP
#define TESTS_QUEUEBUFFER_TESTS_HPP

#include <iostream>
#include "../../Templates/QueueBuffer.hpp"
#include "../Test.hpp"

namespace QueueBufferTests
{

template<typename T, types::Size SIZE>
class BasicTest: public AbstractTest
{
public:
	BasicTest(QueueBuffer<T, SIZE> &queueBuffer) : queue(queueBuffer)
	{
	}

	BasicTest(std::string const &name, QueueBuffer<T, SIZE> &queueBuffer) :
			AbstractTest(name),
			queue(queueBuffer)
	{
	}

	BasicTest(std::string &&name, QueueBuffer<T, SIZE> &queueBuffer) :
			AbstractTest(name),
			queue(queueBuffer)
	{
	}

	BasicTest(const char *name, QueueBuffer<T, SIZE> &queueBuffer) :
			AbstractTest(name),
			queue(queueBuffer)
	{
	}

	virtual ~BasicTest()
	{
	}

protected:
	QueueBuffer<T, SIZE> &queue;
};

template<typename T, types::Size SIZE>
class Push: public BasicTest<T, SIZE>
{
public:
	Push(QueueBuffer<T, SIZE> &queueBuffer) : BasicTest<T, SIZE>("Push", queueBuffer)
	{
	}

	virtual ~Push()
	{
	}

protected:
	virtual int runTest();
};

template<typename T, types::Size SIZE>
class Pop: public BasicTest<T, SIZE>
{
public:
	Pop(QueueBuffer<T, SIZE> &queueBuffer) : BasicTest<T, SIZE>("Pop", queueBuffer)
	{
	}

	virtual ~Pop()
	{
	}

protected:
	virtual int runTest();
};

template<typename T, types::Size SIZE>
class Tail: public BasicTest<T, SIZE>
{
public:
	Tail(QueueBuffer<T, SIZE> &queueBuffer) : BasicTest<T, SIZE>("Tail", queueBuffer)
	{
	}

	virtual ~Tail()
	{
	}

protected:
	virtual int runTest();
};

template<typename T, types::Size SIZE>
class Head: public BasicTest<T, SIZE>
{
public:
	Head(QueueBuffer<T, SIZE> &queueBuffer) : BasicTest<T, SIZE>("Head", queueBuffer)
	{
	}

	virtual ~Head()
	{
	}

protected:
	virtual int runTest();
};

template<typename T, types::Size SIZE>
class Indexes: public BasicTest<T, SIZE>
{
public:
	Indexes(QueueBuffer<T, SIZE> &queueBuffer) : BasicTest<T, SIZE>("Indexes", queueBuffer)
	{
	}

	virtual ~Indexes()
	{
	}

protected:
	virtual int runTest();
};

template<typename T>
class Resize: public BasicTest<T, 0u>
{
public:
	Resize(QueueBuffer<T, 0u> &queueBuffer) : BasicTest<T, 0u>("Resize", queueBuffer)
	{
	}

	virtual ~Resize()
	{
	}

protected:
	virtual int runTest();
};

}

// implementation

template<typename T, types::Size SIZE>
int QueueBufferTests::Push<T, SIZE>::runTest()
{
	int valid = 0;
	if (this->getCountCalls() == 0)
	{
		int array[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

		std::cout << "Addidng elements:";
		for (size_t i = 0; i < sizeof(array) / sizeof(int); ++i)
		{
			this->queue.push(array[i]);
			std::cout << ' ' << array[i];
		}
		std::cout << '\n';

		std::cout << "Added elements:";
		for (size_t i = 0; i < this->queue.size(); ++i)
		{
			std::cout << ' ' << this->queue[i];
		}

		// validating
		for (size_t i = 0; i < this->queue.size(); ++i)
		{
			if (this->queue[i] != array[i])
				++valid;
		}
	}
	else if (this->getCountCalls() == 2)
	{

	}

	std::cout << '\n';

	return valid;
}

template<typename T, types::Size SIZE>
int QueueBufferTests::Pop<T, SIZE>::runTest()
{
	int valid = 0;
	if (this->getCountCalls() == 0)
	{
		std::cout << "Before:";
		for (size_t i = 0; i < this->queue.size(); ++i)
		{
			std::cout << ' ' << this->queue[i];
		}
		std::cout << '\n';
		std::cout.flush();

		int array[] = { 5, 6, 7, 8 };

		size_t max = this->queue.size() / 2;
		for (size_t i = 0; i < max; ++i)
		{
			this->queue.pop();
		}

		std::cout << "After:";
		for (size_t i = 0; i < this->queue.size(); ++i)
		{
			std::cout << ' ' << this->queue[i];
		}

		// validating
		for (size_t i = 0; i < this->queue.size(); ++i)
		{
			if (this->queue[i] != array[i])
				++valid;
		}
	}

	std::cout << '\n';

	return valid;
}

template<typename T, types::Size SIZE>
int QueueBufferTests::Tail<T, SIZE>::runTest()
{
	int valid;
	if (this->queue.head() == 8)
	{
		valid = 0;
	}
	else
	{
		valid = 1;
	}
	return valid;
}

template<typename T, types::Size SIZE>
int QueueBufferTests::Head<T, SIZE>::runTest()
{
	int valid;

	if (this->queue.tail() == 5)
	{
		valid = 0;
	}
	else
	{
		valid = 1;
	}

	return valid;
}

template<typename T>
int QueueBufferTests::Resize<T>::runTest()
{
	return 1;
}

#endif // TESTS_QUEUEBUFFER_TESTS_HPP
