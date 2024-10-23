#include "test_allocate.hpp"
#include <iostream>

int main(){
    Alloc::TestAllocate<int> test;
    int *p = test.allocate(10);
    for (int i = 0; i < 10; i++)
    {
        p[i] = i;
    }
    for (int i = 0; i < 10; i++)
    {
        std::cout << p[i] << std::endl;
    }
    test.deallocate(p);
    return 0;
}