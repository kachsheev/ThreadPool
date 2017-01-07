#ifndef TEST_BASETEST_H
#define TEST_BASETEST_H

#include <string>
#include <vector>
#include <iostream>

//#ifdef __linux
#include "TextStyle.hpp"
//#endif

class AbstractTest
{
public:
	AbstractTest(const AbstractTest &) = delete;
	AbstractTest(AbstractTest &&) = delete;

	AbstractTest() : countCalls(0), testName("Null test")
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
#if defined(__linux)
	void printStart()
	{
		std::cout << "> " TEXT_STYLE_BOLD TEXT_STYLE_CYAN "Start" TEXT_STYLE_NULL " " << testName << '\n';
	}

	void printEnd()
	{
		std::cout << "> " TEXT_STYLE_BOLD TEXT_STYLE_CYAN "End" TEXT_STYLE_NULL " " << testName << "\n\n";
	}

	void printMessageTrue()
	{
		std::cout << "----> " TEXT_STYLE_BOLD TEXT_STYLE_GREEN "SUCCESS TEST\n" TEXT_STYLE_NULL;
	}

	void printMessageFalse()
	{
		std::cout << "----> " TEXT_STYLE_BOLD TEXT_STYLE_RED "FAILED TEST\n" TEXT_STYLE_NULL;
	}
#else
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
#endif

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
//		for(auto it : vtests)
//			delete it;
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

#if defined(__linux)
	void printStart()
	{
		std::cout << TEXT_STYLE_BOLD
				TEXT_STYLE_YELLOW "-------------------- " TEXT_STYLE_NULL
				<< aggregatorName
				<< TEXT_STYLE_BOLD
				TEXT_STYLE_YELLOW " --------------------" TEXT_STYLE_NULL "\n";
	}

	void printEnd()
	{
		std::cout << TEXT_STYLE_BOLD
				TEXT_STYLE_YELLOW "-------------------- " TEXT_STYLE_NULL
				"END"
				<< TEXT_STYLE_BOLD
				TEXT_STYLE_YELLOW " --------------------" TEXT_STYLE_NULL "\n\n";
	}
#else
	void printStart()
	{
		std::cout << "-------------------- "
				<< aggregatorName
				<< " --------------------" "\n";
	}

	void printEnd()
	{
		std::cout << "-------------------- "    "END"     " --------------------" "\n\n";
	}
#endif

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
