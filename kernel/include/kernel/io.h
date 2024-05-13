#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

#include <stdint.h>

extern unsigned char inportb(unsigned short _port);
extern unsigned char outportb(unsigned short _port, unsigned char _data);
extern void EnableInterrupts();
extern void DisableInterrupts();

void iowait();

#endif // !_KERNEL_IO_H
