#include <iostream>
#include "QueueBufferTest.hpp"

using std::cout;

QueueBufferTest::QueueBufferTest()
{
}

QueueBufferTest::~QueueBufferTest()
{
}

void QueueBufferTest::operator()()
{
	for (count = 0; count < 2; ++count)
	{
		push();
		pop();

		if (!count)
		{
			tail();
			head();
		}
	}
}

void QueueBufferTest::push()
{
	cout << "QueueBufferTest.push()\n";

	if (count == 0)
	{
		int array[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

		cout << "Addidng elements:";
		for (size_t i = 0; i < sizeof(array) / sizeof(int); ++i)
		{
			queue.push(array[i]);
			cout << ' ' << array[i];
		}
		cout << '\n';
		cout.flush();

		cout << "Added elements:";
		for (size_t i = 0; i < queue.size(); ++i)
		{
			cout << ' ' << queue[i];
		}
		cout << '\n';
		cout.flush();

		isValid(operatorIndex(array, sizeof(array)/sizeof(array[0])));
	}
	else if (count == 1)
	{

	}

}

void QueueBufferTest::pop()
{
	cout << "QueueBufferTest.pop()\n";

	if (count == 0)
	{
		cout << "Before:";
		for (size_t i = 0; i < queue.size(); ++i)
		{
			cout << ' ' << queue[i];
		}
		cout << '\n';
		cout.flush();

		int array[] = { 5, 6, 7, 8 };

		size_t max = queue.size() / 2;
		for (size_t i = 0; i < max; ++i)
		{
			queue.pop();
		}

		cout << "After:";
		for (size_t i = 0; i < queue.size(); ++i)
		{
			cout << ' ' << queue[i];
		}

		isValid(operatorIndex(array, sizeof(array)/sizeof(array[0])));
	}
	cout << '\n';
	cout.flush();
}

void QueueBufferTest::tail()
{
	cout << "QueueBufferTest.tail()\n";

	bool valid;

	if (queue.head() == 8)
	{
		valid = true;
	}
	else
	{
		valid = false;
	}
	cout << '\n';
	cout.flush();

	isValid(valid);
}

void QueueBufferTest::head()
{
	cout << "QueueBufferTest.head()\n";

	bool valid;

	if (queue.tail() == 5)
	{
		valid = true;
	}
	else
	{
		valid = false;
	}

	isValid(valid);
}
