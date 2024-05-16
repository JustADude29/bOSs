#ifndef _KERNEL_IRQ_H
#define _KERNEL_IRQ_H

#include <stdint.h>

#include <kernel/isrs.h>

typedef void (*IRQHandler)(registers *r);

void irq_init();
void irq_install_handler(int irq, IRQHandler handler);
void irq_uninstall_handler(int irq);

#endif // !_KERNEL_IRQ_H
