#ifndef TESTS_HPP
#define TESTS_HPP

#include <iostream>
#include "../Test.hpp"
#include "../../TaskThread.hpp"

class HelloWorldTask: public AbstractTask
{
public:
	virtual ~HelloWorldTask()
	{
	}

	virtual void operator()()
	{
		std::cout << "Hello, world!";
	}

private:
};


namespace TaskThreadTests
{

class DefaultConstructor: public AbstractTest
{
public:
	DefaultConstructor() :
			AbstractTest("DefaultConstructor"),
			taskThread()
	{
	}

	virtual ~DefaultConstructor()
	{
	}

	TaskThread &getThread()
	{
		return taskThread;
	}

	virtual int runTest();

private:
	TaskThread taskThread;
};

class Constructor: public AbstractTest
{
public:
	static HelloWorldTask hwTask;

	Constructor() :
			AbstractTest("Constructor"),
			taskThread(hwTask)
	{
	}

	virtual ~Constructor()
	{
	}

	TaskThread &getThread()
	{
		return taskThread;
	}

	virtual int runTest();

private:
	TaskThread taskThread;
};

class AddTask: public AbstractTest
{
public:
	AddTask(TaskThread &thread) :
			AbstractTest("AddTask"),
			taskThread(thread)
	{
	}

	virtual ~AddTask()
	{
	}

	virtual int runTest();

private:
	TaskThread &taskThread;
};

class GetStatus: public AbstractTest
{
public:
	GetStatus(TaskThread &thread) :
			AbstractTest("GetStatus"),
			taskThread(thread)
	{
	}

	virtual ~GetStatus()
	{
	}

	virtual int runTest();

private:
	TaskThread &taskThread;
};

class GetTaskStatus: public AbstractTest
{
public:
	GetTaskStatus(TaskThread &thread) :
			AbstractTest("GetStatus"),
			taskThread(thread)
	{
	}

	virtual ~GetTaskStatus()
	{
	}

	virtual int runTest();

private:
	TaskThread &taskThread;
};

}

#endif // TESTS_HPP
