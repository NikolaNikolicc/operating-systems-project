#ifndef _memory_allocator_hpp_
#define _memory_allocator_hpp_

#include "../lib/hw.h"

class MemoryAllocator{
public:

    // dodaj instancu
    static MemoryAllocator& getInstance(){
        static MemoryAllocator instance;
        return instance;
    }

    MemoryAllocator(const MemoryAllocator&) = delete;
    void operator=(MemoryAllocator const&) = delete;

    void* memory_alloc (size_t);

    int memory_free (void*);

private:

    struct FreeMem{
        size_t size;
        FreeMem* next;
        FreeMem* prev;
    };

    FreeMem* fmem_head = nullptr;

    MemoryAllocator(){

        size_t heapStart = (size_t)HEAP_START_ADDR;
        size_t heapEnd = (size_t)HEAP_END_ADDR - 1;

        size_t sizeInBlocks = (heapEnd - heapStart) / MEM_BLOCK_SIZE;

        // poravnaj na prvu krstenu adresu
        fmem_head = (FreeMem*)(heapStart + ((heapStart % MEM_BLOCK_SIZE != 0)?(MEM_BLOCK_SIZE - heapStart % MEM_BLOCK_SIZE) : 0));

        // napravi node

        fmem_head->next = nullptr;
        fmem_head->prev = nullptr;
        fmem_head->size = sizeInBlocks;


    }

//    ~MemoryAllocator(){}

};

#endif