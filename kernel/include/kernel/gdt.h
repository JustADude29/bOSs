#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <stdint.h>
#include <stdio.h>

struct gdt_ptr {
  uint16_t Limit;
  uint16_t Base;
} __attribute__((packed));

struct gdt_entry {
  uint16_t Limit0;
  uint16_t Base0;
  uint8_t Base1;
  uint8_t AccessByte;
  uint8_t Flags;
  uint8_t Base2;
} __attribute__((packed));

struct GDT {
  struct gdt_entry null;
  struct gdt_entry kernel_code;
  struct gdt_entry kernel_data;
};

void gdt_init();

extern void gdt_load(uint64_t);

#endif // !_KERNEL_GDT_H
