#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

#include <stdint.h>
#include <stdio.h>

unsigned char inportb(unsigned short _port);
void outportb(unsigned short _port, unsigned char _data);
extern void EnableInterrupts();
extern void DisableInterrupts();
extern void crasher();

void iowait();

#endif // !_KERNEL_IO_H
