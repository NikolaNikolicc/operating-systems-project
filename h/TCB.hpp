#ifndef _thread_hpp_
#define _thread_hpp_

#include "../lib/hw.h"
#include "../h/scheduler.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/TS.hpp"

class TCB{
public:

    ~TCB(){
        MemoryAllocator::getInstance().memory_free((void*)stack);
    }

    using Body = void (*)(void*);

    // trazene
    static int thread_create(
        TCB** handle,
        void(*start_routine)(void*),
        void* arg,
        void* stack_space,
        bool flag
    );

    static int thread_exit();

    static void thread_dispatch();

    static int time_sleep(uint64 time);

    // getteri i setteri
    void set_finished(bool finished){ this->finished = finished; }

    bool is_finished()const{return finished;}

    void set_next_scheduler(TCB* nextThread){ next_scheduler = nextThread; }

    TCB* get_next_scheduler()const{ return next_scheduler; }

    void set_next_sleep(TCB* nextThread){ next_sleep = nextThread; }

    TCB* get_next_sleep()const{ return next_sleep; }

    void set_next_blocked(TCB* nextThread){ next_blocked = nextThread; }

    TCB* get_next_blocked()const{ return next_blocked; }

    uint64 get_thread_id()const{ return id; }

    uint64 get_time_sleep()const{ return sleep; }

    void set_time_sleep(uint64 new_time){ sleep = new_time; }

    uint64 get_time_slice()const{ return time_slice; }

    static void yield();

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

    // staticka promenljiva
    static TCB* running;
    static TCB* idle;
    static uint64 ID;


protected:


private:

    // konstruktor
    TCB(Body body_init, void* arg, void* stack_space, bool b);

    friend class Riscv;

    struct Context
    {
        uint64 ra;
        uint64 sp;
    };

    static void context_switch(Context *oldContext, Context *runningContext);

    static void thread_wrapper();

    // atributi
    static uint64 time_slice_counter;

    Body body;
    void* argument;
    uint64 *stack;
    Context context;
    bool finished;
    TCB* next_scheduler;
    TCB* next_sleep;
    TCB* next_blocked;
    uint64 sleep;
    uint64 time_slice;
    uint64 id;
    bool flag;
};



#endif