#include <stdio.h>

#include <kernel/gdt.h>
#include <kernel/tty.h>
#include <kernel/idt.h>
#include <kernel/isrs.h>

void kernel_main(void) {
  terminal_initialize();
  gdt_init();
  idt_init();
  isrs_init();

  int n = 10/0;
  putchar(n/0);
  printf("\nHello bOSs\nKaise Ho aap?\n");
}

