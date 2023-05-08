#ifndef _semaphore_hpp_
#define _semaphore_hpp_

#include "../lib/hw.h"
#include "../h/MemoryAllocator.hpp"

class TCB;

class MySemaphore{
public:

    ~MySemaphore(){ sem_close(this);}

    static int sem_open(
          MySemaphore** handle,
          uint64 init
          );
    static int sem_close(MySemaphore* handle);
    static int sem_wait(MySemaphore* id);
    static int sem_signal(MySemaphore* id);

    void put_in_blocked(TCB* tcb);

    TCB* get_from_blocked();

    void block();

    void unblock();

    // getteri i setteri
    bool get_indicator()const{ return indicator; }
    void set_indicator(bool v){ indicator = v; }
    int get_val()const{ return val; }
    void set_val(int v){ val = v; }

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

private:

    MySemaphore(uint64 init);

    int val; // mora da bude signed jer ide i u minus

    bool indicator;

    TCB* head;
    TCB* tail;

};



#endif