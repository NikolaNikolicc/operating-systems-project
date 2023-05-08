#ifndef _my_buffer_hpp_
#define _my_buffer_hpp_

#include "../h/semaphore.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../lib/hw.h"

class MyBuffer {
private:
    int cap;
    int *buffer;
    int head, tail;

    MySemaphore* spaceAvailable;
    MySemaphore* itemAvailable;
    MySemaphore* mutexHead;
    MySemaphore* mutexTail;



public:
    MyBuffer(int _cap);
    ~MyBuffer();

    void put(int val);
    int get();

    int getCnt();

    // operatori
    void *operator new(uint64 n){
        uint64 ssize = (n + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;
        return MemoryAllocator::getInstance().memory_alloc(ssize);
    }

    void *operator new[](uint64 n){
        uint64 ssize = (n + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;
        return MemoryAllocator::getInstance().memory_alloc(ssize);
    }

    void operator delete(void* p)noexcept{
        MemoryAllocator::getInstance().memory_free(p);
    }

    void operator delete[](void* p)noexcept{
        MemoryAllocator::getInstance().memory_free(p);
    }

};


#endif

