#ifndef _syscall_c_h_
#define _syscall_c_h_

#include "../h/abi.hpp"

class _thread;
class _sem;
typedef _thread* thread_t;
typedef _sem* sem_t;
typedef unsigned long time_t;
const int EOF = -1;

extern "C" void* mem_alloc(size_t size);
extern "C" int mem_free(void* addr);
extern "C" int thread_create (
        thread_t* handle,
        void(*start_routine)(void*),
        void* arg
);
extern "C" int thread_exit();
extern "C" void thread_dispatch();
extern "C" int time_sleep (time_t);
extern "C" int sem_open(
        sem_t* handle,
        uint64 init
        );
extern "C" int sem_close(sem_t handle);
extern "C" int sem_wait(sem_t id);
extern "C" int sem_signal(sem_t id);

extern "C" char getc();
extern "C" void putc(char c);

extern "C" void put_in_scheduler(thread_t tcb);

extern "C" void switch_to_user();
extern "C" void switch_to_priviledged();

#endif