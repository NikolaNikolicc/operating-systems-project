#ifndef _thread_sleep_hpp_
#define _thread_sleep_hpp_

class TCB;

class TS{
public:

    static TS& getInstance(){
        static TS instance;
        return instance;
    }

    TS(const TS&) = delete;
    void operator=(TS const&) = delete;

    static void put(TCB* tcb);
    static void decrement_and_remove();

//    static void printTS();

private:
    TS(){head = nullptr;}

    static TCB* head;

};

#endif