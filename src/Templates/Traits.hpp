#ifndef TRAITS_HPP
#define TRAITS_HPP

template<typename T>
struct Traits
{
	typedef T Type;
	typedef T & Reference;
	typedef T && RemoveReference;
	typedef T * Pointer;
	typedef T const & ConstReference;
	typedef T const * PointerToConst;
	typedef T * const ConstPointer;
	typedef const T * const ConstPointerToConst;
};

#endif // TRAITS_HPP
