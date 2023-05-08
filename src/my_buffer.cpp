#include "../h/my_buffer.hpp"

MyBuffer::MyBuffer(int _cap) : cap(_cap + 1), head(0), tail(0) {
    buffer = (int *)MemoryAllocator::getInstance().memory_alloc(sizeof(int) * cap);
    MySemaphore::sem_open(&itemAvailable, 0);
    MySemaphore::sem_open(&spaceAvailable, _cap);
    MySemaphore::sem_open(&mutexHead, 1);
    MySemaphore::sem_open(&mutexTail, 1);
}

MyBuffer::~MyBuffer() {
    MemoryAllocator::getInstance().memory_free((void*)buffer);
    MySemaphore::sem_close(itemAvailable);
    MySemaphore::sem_close(spaceAvailable);
    MySemaphore::sem_close(mutexTail);
    MySemaphore::sem_close(mutexHead);
}

void MyBuffer::put(int val) {
    MySemaphore::sem_wait(spaceAvailable);

    MySemaphore::sem_wait(mutexTail);
    buffer[tail] = val;
    tail = (tail + 1) % cap;
    MySemaphore::sem_signal(mutexTail);

    MySemaphore::sem_signal(itemAvailable);

}

int MyBuffer::get() {
    MySemaphore::sem_wait(itemAvailable);

    MySemaphore::sem_wait(mutexHead);

    int ret = buffer[head];
    head = (head + 1) % cap;
    MySemaphore::sem_signal(mutexHead);

    MySemaphore::sem_signal(spaceAvailable);

    return ret;
}

int MyBuffer::getCnt() {
    int ret;

    MySemaphore::sem_wait(mutexHead);
    MySemaphore::sem_wait(mutexTail);

    if (tail >= head) {
        ret = tail - head;
    } else {
        ret = cap - head + tail;
    }

    MySemaphore::sem_signal(mutexTail);
    MySemaphore::sem_signal(mutexHead);

    return ret;
}
