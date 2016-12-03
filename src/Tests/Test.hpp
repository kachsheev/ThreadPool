#ifndef TEST_BASETEST_H
#define TEST_BASETEST_H

#include <string>
#include <vector>
#include <iostream>

#ifdef __linux
#include "TextStyle.hpp"
#endif

template<typename T>
class AbstractTest
{
public:
	AbstractTest(const AbstractTest &) = delete;
	AbstractTest(AbstractTest &&) = delete;

	AbstractTest() : testName("Null test")
	{
	}
	AbstractTest(std::string const &name) : testName(name)
	{
	}
	AbstractTest(std::string &&name) : testName(name)
	{
	}
	AbstractTest(char const *nameStr)   :  testName(nameStr)
	{
	}

	virtual ~AbstractTest()
	{
	}

	void operator()()
	{
		int returnCode;

		printStart();

		returnCode = start();
		if(returnCode)
		{
			printMessageFalse();
		}
		else
		{
			printMessageTrue();
		}

		printEnd();

		return returnCode;
	}

protected:
	virtual int start() = 0;

private:
	void printStart()
	{
#	if defined(__linux)
		std::cout << "> " TEXT_STYLE_BOLD TEXT_STYLE_CYAN "Start" TEXT_STYLE_NULL " " << testName << '\n';
#	else
		std::cout << "> Start " << __name << '\n';
#	endif
	}

	void printEnd()
	{
#	if defined(__linux)
		std::cout << "> " TEXT_STYLE_BOLD TEXT_STYLE_CYAN "End" TEXT_STYLE_NULL " " << testName << "\n\n";
#	else
		std::cout << "> End " << __name << "\n\n";
#	endif
	}

	void printMessageTrue()
	{
#	if defined(__linux)
		std::cout << "----> " TEXT_STYLE_BOLD TEXT_STYLE_GREEN "SUCCESS TEST\n" TEXT_STYLE_NULL;
#	else
		std::cout << "----> SUCCESS TEST\n";
#	endif
	}

	void printMessageFalse()
	{
#	if defined(__linux)
		std::cout << "----> " TEXT_STYLE_BOLD TEXT_STYLE_RED "FAILED TEST\n" TEXT_STYLE_NULL;
#	else
		std::cout << "----> FAILED TEST\n";
#	endif
	}

	std::string testName;
};


template<typename T>
class TestAggregator
{
public:
	TestAggregator(const TestAggregator<T> &) = delete;
	TestAggregator(TestAggregator<T> &&) = delete;

	TestAggregator() : aggregatorName("NONAME")
	{
	}
	TestAggregator(char const *name) : aggregatorName(name)
	{
	}
	TestAggregator(std::string const &name) : aggregatorName(name)
	{
	}
	TestAggregator(std::string &&name) : aggregatorName(name)
	{
	}

	~TestAggregator()
	{
		for(auto it : vtests)
			delete it;
	}

	void start()
	{
		printStart();
		startTests();
		printEnd();
	}

	void pushBackTest(AbstractTest<T> *test, int is_enable = 1)
	{
		vtests.push_back(test);
		enableTests.push_back(is_enable);
	}

	virtual void printStatistic() const
	{
	}

protected:
	std::vector<int> returnCodes;
	std::vector<int> enableTests;

	virtual void startTests()
	{
		AbstractTest<T> *test;
		for(auto it = vtests.begin(); it != vtests.end(); ++it)
		{
			test = *it;
			returnCodes.push_back(test->start());
		}
	}

	void printStart()
	{
#	if defined(__linux)
		std::cout << TEXT_STYLE_BOLD TEXT_STYLE_YELLOW "-------------------- " TEXT_STYLE_NULL
				  << aggregatorName
				  << TEXT_STYLE_BOLD TEXT_STYLE_YELLOW " --------------------" TEXT_STYLE_NULL "\n";
#	else
		std::cout << "-------------------- " << __name << " --------------------" "\n";
#	endif
	}

	void printEnd()
	{
#	if defined(__linux)
		std::cout << TEXT_STYLE_BOLD TEXT_STYLE_YELLOW "-------------------- " TEXT_STYLE_NULL
					 "END"
					 TEXT_STYLE_BOLD TEXT_STYLE_YELLOW " --------------------" TEXT_STYLE_NULL "\n\n";
#	else
		std::cout << "-------------------- "    "END"     " --------------------" "\n\n";
#	endif
	}

	std::string getName() const
	{
		return aggregatorName;
	}
	std::string &getName()
	{
		return aggregatorName;
	}

	void setName(const std::string &new_name)
	{
		aggregatorName = new_name;
	}
	void setName(std::string &&new_name)
	{
		aggregatorName = new_name;
	}

private:

	std::string aggregatorName;
	std::vector<AbstractTest<T> *> vtests;
};

#endif // TEST_BASETEST_H
