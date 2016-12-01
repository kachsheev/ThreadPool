#ifndef TESTS_ALLTESTS_HPP
#define TESTS_ALLTESTS_HPP

#include <AbstractTask.hpp>

class AllTests: public AbstractTask
{
public:
	AllTests();
	virtual ~AllTests();

	virtual void operator ()();
private:
	void testQueueBuffer();
	void testThreadPool();
};

#endif // ALLTESTS_HPP
