#ifndef TASK_HPP
#define TASK_HPP

class AbstractTask
{
public:
	virtual ~AbstractTask()
	{
	}

protected:
	virtual void operator()() = 0;

	friend class ThreadPool;
};

#endif // TASK_HPP
