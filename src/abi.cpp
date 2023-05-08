#include "../h/abi.hpp"

void* abi::sys_call(void *param) {
    __asm__ volatile("ld a1, 8(a0)");
    __asm__ volatile("ld a2, 16(a0)");
    __asm__ volatile("ld a3, 24(a0)");
    __asm__ volatile("ld a4, 32(a0)");
    __asm__ volatile("ld a5, 40(a0)");
    __asm__ volatile("ld a6, 48(a0)");
    __asm__ volatile("ld a7, 56(a0)");
    __asm__ volatile("ld a0, (a0)");

    __asm__ volatile("ecall");
    // u a0 se nalazi povratna vrednost
    uint64 ret0;
    __asm__ volatile("mv %[ret], a0" : [ret]"=r"(ret0));
    return (void*)ret0;
}
