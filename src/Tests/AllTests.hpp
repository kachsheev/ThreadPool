#ifndef TESTS_ALLTESTS_HPP
#define TESTS_ALLTESTS_HPP

#include "../AbstractTask.hpp"

class AllTests
{
public:
	AllTests();
	~AllTests();

	void operator ()();
private:
	void testQueueBuffer();
	void testTaskThread();
	void testThreadPool();
};

#endif // ALLTESTS_HPP
