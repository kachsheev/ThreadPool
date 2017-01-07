#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>

namespace types
{

typedef std::size_t Size;
typedef std::uint64_t Uint64;
typedef void*(*ThreadTaskType)(void *);

enum class TaskStatus
{
	FAILED,
	MISSED,
	QUEUED,
	PROCESS,
	FINISHED
};

enum class ThreadType
{
	QUEUE,
	SIMPLE
};

}

#endif // TYPES_HPP
