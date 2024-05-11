#ifndef _KERNEL_IDT_H
#define _KERNEL_IDT_H

#include <stdint.h>
#include <stdio.h>

struct idt_ptr {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

struct idt_entry {
  unsigned short base_low;
  unsigned short sel;
  unsigned char redundant;
  unsigned char flags;
  unsigned short base_high;
} __attribute__((packed));

void idt_init();

void set_idt_gate(unsigned int num, unsigned int base, unsigned short sel,
                  unsigned char flags);

#endif // !_KERNEL_IDT_H
