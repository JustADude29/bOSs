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

typedef enum
{
    IDT_FLAG_GATE_TASK              = 0x5,
    IDT_FLAG_GATE_16BIT_INT         = 0x6,
    IDT_FLAG_GATE_16BIT_TRAP        = 0x7,
    IDT_FLAG_GATE_32BIT_INT         = 0xE,
    IDT_FLAG_GATE_32BIT_TRAP        = 0xF,

    IDT_FLAG_RING0                  = (0 << 5),
    IDT_FLAG_RING1                  = (1 << 5),
    IDT_FLAG_RING2                  = (2 << 5),
    IDT_FLAG_RING3                  = (3 << 5),

    IDT_FLAG_PRESENT                = 0x80,

} IDT_FLAGS;

void idt_disableGate(int interrupt);
void idt_enableGate(int interrupt);

#endif // !_KERNEL_IDT_H
