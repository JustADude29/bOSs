#ifndef _HAL_HAL_H
#define _HAL_HAL_H

#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/io.h>
#include <kernel/irq.h>
#include <kernel/isrs.h>
#include <kernel/multiboot.h>
#include <kernel/tty.h>

#include <drivers/keyboard.h>
#include <drivers/pit.h>

void hal_init();

void hal_detect_memory(multiboot_info_t *mbd, unsigned int magic);

#endif // !_HAL_HAL_H
