/*
 * file:       RwLocker
 *
 * created:    02.12.2016
 * author:     kachsheev
 */
#ifndef RWLOCKER_HPP
#define RWLOCKER_HPP

#include "../Types.hpp"
#include "../Semaphore.hpp"
#include "QueueBuffer.hpp"

template<typename T, types::Size SIZE>
struct RwLockQueueBuffer
{
	RwLockQueueBuffer() : rwLock(1)
	{
	}

	void push(T &&t)
	{
		Semaphore::Locker locker(rwLock);
		queue.push(t);
	}

	T pop()
	{
		Semaphore::Locker locker(rwLock);
		T t = queue.pop();
		return t;
	}

	T &head()
	{
		Semaphore::Locker locker(rwLock);
		return queue.head();
	}

	types::Size size()
	{
		Semaphore::Locker locker(rwLock);
		return queue.size();
	}

	T &operator[](types::Size index)
	{
		Semaphore::Locker locker(rwLock);
		return queue[index];
	}

private:
	QueueBuffer<T, SIZE> queue;
	Semaphore rwLock;
};


#endif // RWLOCKER_HPP
