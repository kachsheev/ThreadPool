#ifndef QUEUEBUFFER_HPP
#define QUEUEBUFFER_HPP

#include "../Types.hpp"

// declaration
template<typename T, types::Size SIZE>
class QueueBuffer
{
public:
	QueueBuffer();
	~QueueBuffer();

	void push(const T &object);
	T pop();

	T &tail();
	T &head();

	T &operator[](types::Size index);

	T *data();

	types::Size size() const noexcept;
	constexpr types::Size capacity() const noexcept;

	const T &tail() const;
	const T &head() const;

	const T &operator[](types::Size index) const;

	const T *data() const;

private:
	T queue[SIZE];
	types::Size indexHead;
	types::Size indexTail;
	types::Size queueSize;
};

// implementation
template<typename T, types::Size SIZE>
QueueBuffer<T, SIZE>::QueueBuffer() :
		queue{}, indexHead(0), indexTail(0), queueSize(0)
{
}

template<typename T, types::Size SIZE>
QueueBuffer<T, SIZE>::~QueueBuffer()
{
}

// non-const
template<typename T, types::Size SIZE>
void QueueBuffer<T, SIZE>::push(const T &object)
{
	if (size())
	{
		if (indexHead + 1 == capacity())
		{
			indexHead = 0;
		}
		else
		{
			++indexHead;
		}
	}
	++queueSize;
	queue[indexHead] = object;
}

template<typename T, types::Size SIZE>
T QueueBuffer<T, SIZE>::pop()
{
	if (size())
	{
		T object = queue[indexTail];
		if (indexTail + 1 == capacity())
		{
			indexTail = 0;
		}
		else
		{
			++indexTail;
		}
		--queueSize;
		return object;
	}
	else
	{
		return T{};
	}
}

template<typename T, types::Size SIZE>
T &QueueBuffer<T, SIZE>::tail()
{
	return queue[indexTail];
}

template<typename T, types::Size SIZE>
T &QueueBuffer<T, SIZE>::head()
{
	return queue[indexHead];
}

template<typename T, types::Size SIZE>
T &QueueBuffer<T, SIZE>::operator[](types::Size index)
{
	types::Size realIndex = ((indexTail + index >= capacity())
			? SIZE - indexTail + index
			: indexTail + index);
	return queue[realIndex];
}

template<typename T, types::Size SIZE>
T *QueueBuffer<T, SIZE>::data()
{
	return &queue[0];
}

// const
template<typename T, types::Size SIZE>
types::Size QueueBuffer<T, SIZE>::size() const noexcept
{
	return queueSize;
}

template<typename T, types::Size SIZE> constexpr
types::Size QueueBuffer<T, SIZE>::capacity() const noexcept
{
	return SIZE;
}

template<typename T, types::Size SIZE>
const T &QueueBuffer<T, SIZE>::tail() const
{
	return queue[indexTail];
}

template<typename T, types::Size SIZE>
const T &QueueBuffer<T, SIZE>::head() const
{
	return queue[indexHead];
}

template<typename T, types::Size SIZE>
const T &QueueBuffer<T, SIZE>::operator [](types::Size index) const
{
	types::Size realIndex = ((indexTail + index >= capacity())
			? SIZE - indexTail + index
			: indexTail + index);
	return queue[realIndex];
}

template<typename T, types::Size SIZE>
const T *QueueBuffer<T, SIZE>::data() const
{
	return &queue[0];
}

#endif // QUEUEBUFFER_HPP
