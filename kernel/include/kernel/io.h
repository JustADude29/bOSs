#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

#include <stdint.h>
#include <stdio.h>

#include <kernel/tty.h>

unsigned char inportb(unsigned short _port);
void outportb(unsigned short _port, unsigned char _data);
extern void EnableInterrupts();
extern void DisableInterrupts();
extern void crasher();

void iowait();
void panic(char *error);

#endif // !_KERNEL_IO_H
