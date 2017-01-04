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

	virtual ~BasicTest()
	{
	}

protected:
	size_t count;
	QueueBuffer<T, SIZE> &queue;
};

template<typename T, types::Size SIZE>
class Push: public BasicTest<T, SIZE>
{
public:
	Push(QueueBuffer<T, SIZE> &queueBuffer) : BasicTest<T, SIZE>(queueBuffer)
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
	Pop(QueueBuffer<T, SIZE> &queueBuffer) : BasicTest<T, SIZE>(queueBuffer)
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
	Tail(QueueBuffer<T, SIZE> &queueBuffer) : BasicTest<T, SIZE>(queueBuffer)
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
	Head(QueueBuffer<T, SIZE> &queueBuffer) : BasicTest<T, SIZE>(queueBuffer)
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
	Indexes(QueueBuffer<T, SIZE> &queueBuffer) : BasicTest<T, SIZE>(queueBuffer)
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
	Resize(QueueBuffer<T, 0u> &queueBuffer) : BasicTest<T, 0u>(queueBuffer)
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
	std::cout << "QueueBufferTest::Push<T, SIZE>::runTest()\n";

	int valid = 0;
	if (this->count == 0)
	{
		int array[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

		std::cout << "Addidng elements:";
		for (size_t i = 0; i < sizeof(array) / sizeof(int); ++i)
		{
			this->queue.push(array[i]);
			std::cout << ' ' << array[i];
		}
		std::cout << '\n';
		std::cout.flush();

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
	else if (this->count == 1)
	{

	}

	std::cout << '\n';
	std::cout.flush();

	return valid;
}

template<typename T, types::Size SIZE>
int QueueBufferTests::Pop<T, SIZE>::runTest()
{
	std::cout << "QueueBufferTest::Pop<T, SIZE>::runTest()\n";

	int valid = 0;
	if (this->count == 0)
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
	std::cout.flush();

	return valid;
}

template<typename T, types::Size SIZE>
int QueueBufferTests::Tail<T, SIZE>::runTest()
{
	std::cout << "QueueBufferTests::Tail<T, SIZE>::runTest()\n";

	int valid;

	if (this->queue.head() == 8)
	{
		valid = 0;
	}
	else
	{
		valid = 1;
	}
	std::cout << '\n';
	std::cout.flush();

	return valid;
}

template<typename T, types::Size SIZE>
int QueueBufferTests::Head<T, SIZE>::runTest()
{
	std::cout << "QueueBufferTests::Head<T, SIZE>::runTest()\n";

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
	std::cout << "QueueBufferTests::Resize<T>::runTest()\n";

	return 1;
}

#endif // TESTS_QUEUEBUFFER_TESTS_HPP
