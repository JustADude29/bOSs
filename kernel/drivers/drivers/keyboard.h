#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

#include <kernel/irq.h>
#include <kernel/io.h>

#include <stdio.h>
#include <stdint.h>

void keyboard_handler(registers* r);

void keyboard_init();

#endif // !_KERNEL_KEYBOARD_H

