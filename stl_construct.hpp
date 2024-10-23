#ifndef _STL_CONSTRUCT_HPP
#define _STL_CONSTRUCT_HPP
#include <new>
#include <iostream>
#include <type_traits>

template<class T1, class T2>
inline void construct(T1* p, const T2& value)
{
    // placement new
    new(p) T1(value);
}

template<class T>
inline void destroy(T* p)
{
    p->~T();
}

template<class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
    __destroy(first, last, value_type(first));
}

template<class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*)
{
    typedef typename std::is_trivially_destructible<T> trivial_destructor;
    __destroy_aux(first, last, trivial_destructor());
}

template<class ForwardIterator, class T>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last, std::false_type)
{
    for(; first != last; ++first)
    {
        // 通过迭代器找到对应的元素指针
        // 才可以执行第一个的destroy函数
        destroy(&*first);
    }
}

// 如果是平凡类型，就不需要显式调用析构函数
template <class ForwardIterator, class T>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last, std::true_type) {}

// 针对char*和wchar_t*的特化版本
template<>
inline void __destroy_aux<char*, std::true_type>(char* first, char* last, std::true_type) {}

template<>
inline void __destroy_aux<wchar_t*, std::true_type>(wchar_t* first, wchar_t* last, std::true_type) {}

#endif