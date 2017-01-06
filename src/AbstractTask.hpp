#ifndef TASK_HPP
#define TASK_HPP

class AbstractTask
{
public:
	virtual ~AbstractTask()
	{
	}

	virtual void operator()() = 0;

protected:
	friend class ThreadPool;
};

#endif // TASK_HPP
