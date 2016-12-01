#ifndef ABSTRACTTEST_HPP
#define ABSTRACTTEST_HPP

#include <iostream>

class AbstractTest
{
public:
	virtual ~AbstractTest()
	{
	}

	virtual void operator()() = 0;
	void start()
	{
		this->operator ()();
	}

protected:
	void isValid(bool valid);

	void incCounter()
	{
		++counter;
	}

	void decCounter()
	{
		--counter;
	}

	size_t getCounter()
	{
		return counter;
	}

private:
	size_t counter;
};

#endif // ABSTRACTTEST_HPP
