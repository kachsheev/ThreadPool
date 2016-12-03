/*
 * file:       Thread.cpp
 *
 * created:    02.12.2016
 * author:     kachsheev
 */
#include "Thread.hpp"

Thread::Thread(): descriptor()
{
}

Thread::~Thread()
{
	join();
}

void Thread::start()
{
	pthread_create(&descriptor.get(), &descriptor.attributes(), Thread::threadTask, nullptr);
}

void Thread::join()
{
	pthread_join(descriptor.get(), nullptr);
}

void Thread::cancel()
{
	pthread_cancel(descriptor.get());
}

void *Thread::threadTask(void *data)
{
	Thread *thread = reinterpret_cast<Thread *>(data);
	thread->run();
	return nullptr;
}
