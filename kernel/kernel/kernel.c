#include <stdio.h>

#include <kernel/gdt.h>
#include <kernel/tty.h>
#include <kernel/idt.h>
#include <kernel/isrs.h>
#include <kernel/irq.h>

void kernel_main(void) {
  terminal_initialize();
  gdt_init();
  idt_init();
  isrs_init();
  irq_init();

  printf("\nHello bOSs\nKaise Ho aap?\n");
}

