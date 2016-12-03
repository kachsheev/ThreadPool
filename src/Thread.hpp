/*
 * file:       Thread.hpp
 *
 * created:    02.12.2016
 * author:     kachsheev
 */
#ifndef THREAD_HPP
#define THREAD_HPP

#include "Types.hpp"
#include "Descriptor.hpp"
#include "Mutex.hpp"

class Thread
{
public:
	Thread();
	virtual ~Thread();

	void start();
	void join();
	void cancel();

protected:
	virtual void run() = 0;

private:
	Descriptor descriptor;

	static void *threadTask(void *data);
};

#endif // THREAD_HPP
