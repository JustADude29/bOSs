#ifndef _KERNEL_PIT_H
#define _KERNEL_PIT_H

#include <kernel/irq.h>
#include <kernel/io.h>
#include <kernel/tty.h>

#include <stdint.h>

static unsigned int timer_ticks = 0;
static unsigned int timer_freq = 18;

void set_timer_phase(int hz);

void timer_handler(registers *r);

void timer_init();

#endif // !_KERNEL_TIMER_H
