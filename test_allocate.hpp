#ifndef _TEST_ALLOCATE_HPP_
#define _TEST_ALLOCATE_HPP_
#include <iostream>
#include <new>
#include <memory>
#include <thread>
#include <climits>

#define ALLOC_OK 0
#define ALLOC_FAIL 1
#define ALLOC_ERROR 2

namespace Alloc
{
    // void self_new_handle(){
    //     std::cerr << "Status: " << ALLOC_FAIL << std::endl;
    //     exit(ALLOC_FAIL);
    // }

    template<class T>
    inline T* _allocate(size_t n)
    {
        std::set_new_handler(0);
        T* temp = static_cast<T*>(::operator new(n * sizeof(T)));
        if (temp == nullptr)
        {
            std::cerr << "allocate failed" << std::endl;
            exit(ALLOC_FAIL);
        }
        return temp;
    }

    template<class T>
    inline void _deallocate(void *p)
    {
        ::operator delete(p);
    }


    template <typename T>
    class TestAllocate
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef size_t size_type;
        typedef std::ptrdiff_t difference_type;

    public:
        TestAllocate() = default;
        TestAllocate(const TestAllocate &) = default;
        TestAllocate &operator=(const TestAllocate &) = default;
        TestAllocate(TestAllocate &&) = default;
        ~TestAllocate() = default;

        pointer allocate(size_type n)
        {
            return _allocate<value_type>(n);
        }

        void deallocate(pointer p)
        {
            _deallocate<value_type>(p);
        }

        pointer address(reference x) const
        {
            return &x;
        }

    };

}

#endif // _TEST_ALLOCATE_HPP_