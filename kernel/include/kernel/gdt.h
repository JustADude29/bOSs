#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <stdint.h>
#include <stdio.h>

struct gdt_ptr {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

struct gdt_entry {
  unsigned short limit;
  unsigned short base_low;
  unsigned char base_middle;
  unsigned char access;
  unsigned char flags;
  unsigned char base_high;
} __attribute__((packed));

void gdt_init();

void set_gdt_gate(unsigned int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char flags);

#endif // !_KERNEL_GDT_H
