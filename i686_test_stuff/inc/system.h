#ifndef _TYPES_
#define _TYPES_

#include "types.h"

u8 inportb(u16 _port){
    u8 rv;
    __asm__ __volatile__("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb(u16 _port, u8 _data){
    __asm__ __volatile__("outb %1, %0" : : "dN" (_port), "a" (_data));
}

#endif