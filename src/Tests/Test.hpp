#ifndef TEST_BASETEST_H
#define TEST_BASETEST_H

#include <string>
#include <vector>
#include <iostream>

#include "TextStyle.hpp"

class AbstractTest
{
public:
	AbstractTest(const AbstractTest &) = delete;
	AbstractTest(AbstractTest &&) = delete;

	AbstractTest() :
			countCalls(0),
			testName("Null test")
	{
	}
	AbstractTest(std::string const &name) :
			countCalls(0),
			testName(name)
	{
	}
	AbstractTest(std::string &&name) :
			countCalls(0),
			testName(name)
	{
	}
	AbstractTest(char const *nameStr) :
			countCalls(0),
			testName(nameStr)
	{
	}

	virtual ~AbstractTest()
	{
	}

	int operator()()
	{
		int returnCode;

		printStart();

		returnCode = runTest();
		if(returnCode)
		{
			printMessageFalse();
		}
		else
		{
			printMessageTrue();
		}

		printEnd();

		++countCalls;

		return returnCode;
	}

protected:
	unsigned int getCountCalls() const
	{
		return countCalls;
	}

	virtual int runTest() = 0;

private:
	void printStart()
	{
		std::cout << "> ";
		setConsoleText(TEXT_CYAN, TEXT_BACKGROUND_BLACK);
		std::cout << "Start" " " << testName << '\n';
		setConsoleText(TEXT_WHITE, TEXT_BACKGROUND_BLACK);
	}

	void printEnd()
	{
		std::cout << "> ";
		setConsoleText(TEXT_CYAN, TEXT_BACKGROUND_BLACK);
		std::cout << "End" " " << testName << "\n\n";
		setConsoleText(TEXT_WHITE, TEXT_BACKGROUND_BLACK);
	}

	void printMessageTrue()
	{
		std::cout << "----> ";
		setConsoleText(TEXT_GREEN, TEXT_BACKGROUND_BLACK);
		std::cout << "SUCCESS TEST\n";
		setConsoleText(TEXT_WHITE, TEXT_BACKGROUND_BLACK);
	}

	void printMessageFalse()
	{
		std::cout << "----> ";
		setConsoleText(TEXT_RED, TEXT_BACKGROUND_BLACK);
		std::cout << "FAILED TEST\n";
		setConsoleText(TEXT_WHITE, TEXT_BACKGROUND_BLACK);
	}

	unsigned int countCalls;
	std::string testName;

	friend class TestAggregator;
};

class TestAggregator
{
public:
	TestAggregator(const TestAggregator &) = delete;
	TestAggregator(TestAggregator &&) = delete;

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

	virtual ~TestAggregator()
	{
	}

	void start()
	{
		printStart();
		startTests();
		printEnd();
	}

	void pushBackTest(AbstractTest *test, int isEnable = 1)
	{
		vtests.push_back(test);
		enableTests.push_back(isEnable);
	}

	virtual void printStatistic() const
	{
	}

protected:
	std::vector<int> returnCodes;
	std::vector<int> enableTests;

	virtual void startTests()
	{
		AbstractTest *test;
		for(auto it = vtests.begin(); it != vtests.end(); ++it)
		{
			test = *it;
			returnCodes.push_back((*test)());
		}
	}

	void printStart()
	{
		std::cout << "-------------------- ";
		setConsoleText(TEXT_YELLOW, TEXT_BACKGROUND_BLACK);
		std::cout << aggregatorName;
		setConsoleText(TEXT_WHITE, TEXT_BACKGROUND_BLACK);
		std::cout << " --------------------" "\n";
	}

	void printEnd()
	{
		std::cout << "-------------------- ";
		setConsoleText(TEXT_YELLOW, TEXT_BACKGROUND_BLACK);
		std::cout << "END";
		setConsoleText(TEXT_WHITE, TEXT_BACKGROUND_BLACK);
		std::cout << " --------------------" "\n\n";
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
	std::vector<AbstractTest *> vtests;
};

#endif // TEST_BASETEST_H
