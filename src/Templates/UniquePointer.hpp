#ifndef UNIQUEPOINTER_HPP
#define UNIQUEPOINTER_HPP

#include "Traits.hpp"

template<typename T>
class UniquePointer
{
public:
	typedef Traits<T> TypeTraits;
	typedef Traits<UniquePointer<T>> MyTraits;

	UniquePointer()
	{
		data = new T;
	}

	UniquePointer(typename MyTraits::RemoveReference pointer) noexcept
	{
		data = pointer.data;
		pointer.data = nullptr;
	}

	template<typename ... Args>
	UniquePointer(Args ... args)
	{
		data = new T(args ...);
	}

	~UniquePointer()
	{
		delete data;
	}

	typename TypeTraits::Reference operator*() noexcept
	{
		return *data;
	}
	typename TypeTraits::ConstReference operator*() const noexcept
	{
		return *data;
	}

	typename TypeTraits::Pointer operator->() noexcept
	{
		return data;
	}
	typename TypeTraits::PointerToConst operator->() const noexcept
	{
		return data;
	}

	typename MyTraits::Reference operator=(typename MyTraits::RemoveReference pointer)
	{
		data = pointer.data;
		pointer.data = nullptr;
		return *this;
	}

private:
	UniquePointer(const UniquePointer<T> &) = delete;
	typename MyTraits::Reference operator=(typename MyTraits::ConstReference) = delete;

	typename TypeTraits::Pointer data;
};

template<typename T, typename ... Args>
UniquePointer<T> makeUnique(Args ... args)
{
	return UniquePointer<T>(args ...);
}

#endif // UNIQUEPOINTER_HPP
