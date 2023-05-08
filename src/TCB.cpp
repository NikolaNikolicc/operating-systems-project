#include "../h/TCB.hpp"
#include "../h/riscv.hpp"

TCB* TCB::running = nullptr;
TCB* TCB::idle = nullptr;
uint64 TCB::time_slice_counter = 0;
uint64 TCB::ID = 0;

int TCB::thread_create(TCB **handle,
                       void (*start_routine)(void *),
                       void *arg,
                       void* stack_space,
                       bool flag
                       ) {
    TCB* tmp = (TCB*)new TCB(start_routine, arg, stack_space, flag);
    *handle = tmp;
    if (start_routine != nullptr && tmp != TCB::idle && flag) {
        Scheduler::getInstance().put(tmp);
    }
    if(*handle) return 0;
    else return -1;
}

int TCB::thread_exit() {
    running->set_finished(true);
    TCB::thread_dispatch();
    // do ovog dela nece nikad doci jer thread_dispatch nece nit koju gasimo staviti u scheduler
    return -1;
}

void TCB::thread_dispatch() {
//    Scheduler::printScheduler();
    TCB * old = running;
    running = Scheduler::getInstance().get();
    if (!old->is_finished()) {
        Scheduler::getInstance().put(old);
    }
    else{
        TCB::operator delete(old);
    }
//    TCB::time_slice_counter = 0;
    TCB::context_switch(&old->context, &running->context);
}

void TCB::thread_wrapper() {
    Riscv::popSppSpie();
    running->body(running->argument);
    thread_exit();
}

TCB::TCB(Body body_init, void *arg, void *stack_space, bool b) {
    body = body_init;
    argument = arg;
    stack = (uint64*)stack_space;
    context.ra = (uint64) &thread_wrapper;
    context.sp = stack_space != nullptr ? (uint64) &stack[DEFAULT_STACK_SIZE / sizeof(uint64)] : 0;
    finished = false;
    next_scheduler = nullptr;
    next_sleep = nullptr;
    next_blocked = nullptr;
    time_slice = DEFAULT_TIME_SLICE;
    sleep = 0;
    id = ID++;
    flag = b;
}

int TCB::time_sleep(uint64 time) {

    running->set_time_sleep(time);
    TS::getInstance().put(running);
    TCB::yield();
    return 0;
}

void TCB::yield() {
    TCB * old = running;
    running = Scheduler::getInstance().get();
    TCB::time_slice_counter = 0;
    TCB::context_switch(&old->context, &running->context);
}


