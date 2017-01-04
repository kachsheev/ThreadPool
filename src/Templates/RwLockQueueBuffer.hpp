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

	void push(const T &t)
	{
		volatile Semaphore::Locker locker(rwLock);
		queue.push(t);
	}

	void push(T &&t)
	{
		volatile Semaphore::Locker locker(rwLock);
		queue.push(t);
	}

	T pop()
	{
		volatile Semaphore::Locker locker(rwLock);
		T t = queue.pop();
		return t;
	}

	T &head()
	{
		volatile Semaphore::Locker locker(rwLock);
		return queue.head();
	}

	types::Size size()
	{
		volatile Semaphore::Locker locker(rwLock);
		return queue.size();
	}

	types::Size capacity()
	{
		volatile Semaphore::Locker locker(rwLock);
		return queue.capacity();
	}

	T &operator[](types::Size index)
	{
		volatile Semaphore::Locker locker(rwLock);
		return queue[index];
	}

private:
	QueueBuffer<T, SIZE> queue;
	Semaphore rwLock;
};

template<typename T>
struct RwLockQueueBuffer<T, 0u>
{
	RwLockQueueBuffer() : rwLock(1)
	{
	}

	void push(const T &t)
	{
		volatile Semaphore::Locker locker(rwLock);
		queue.push(t);
	}

	void push(T &&t)
	{
		volatile Semaphore::Locker locker(rwLock);
		queue.push(t);
	}

	T pop()
	{
		volatile Semaphore::Locker locker(rwLock);
		T t = queue.pop();
		return t;
	}

	T &head()
	{
		volatile Semaphore::Locker locker(rwLock);
		return queue.head();
	}

	types::Size size() const
	{
		volatile Semaphore::Locker locker(rwLock);
		return queue.size();
	}

	types::Size capacity() const
	{
		volatile Semaphore::Locker locker(rwLock);
		return queue.capacity();
	}

	T &operator[](types::Size index)
	{
		volatile Semaphore::Locker locker(rwLock);
		return queue[index];
	}

	const T &operator[](types::Size index) const
	{
		volatile Semaphore::Locker locker(rwLock);
		return queue[index];
	}

	void resize(types::Size newSize)
	{
		volatile Semaphore::Locker locker(rwLock);
		queue.resize(newSize);
	}

private:
	QueueBuffer<T, 0u> queue;
	mutable Semaphore rwLock;
};

#endif // RWLOCKER_HPP
