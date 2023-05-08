#ifndef _scheduler_hpp_
#define _scheduler_hpp_

//#include "../test/printing.hpp"

class TCB;

class Scheduler{
public:

    static Scheduler& getInstance(){
        static Scheduler instance;
        return instance;
    }

    Scheduler(const Scheduler&) = delete;
    void operator=(Scheduler const&) = delete;

    TCB* get();

    void put(TCB* tcb);

//    static void printScheduler();

private:

    Scheduler(){
        head = nullptr;
        tail = nullptr;
    }

    static TCB* head;
    static TCB* tail;
};

#endif
