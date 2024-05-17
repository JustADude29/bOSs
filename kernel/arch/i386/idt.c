#include <kernel/idt.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <utils/binary.h>

extern void idt_load(idt_ptr* idtp);

idt_entry idt_entries[256];
idt_ptr idtp = { sizeof(idt_entries) - 1, idt_entries };

void set_idt_gate(unsigned int num, unsigned int base, unsigned short sel,
                  unsigned char flags) {
  idt_entries[num].redundant = 0;
  idt_entries[num].flags = flags;
  idt_entries[num].sel = sel;

  idt_entries[num].base_low = (base & 0xFFFF);
  idt_entries[num].base_high = (base >> 16) & 0xFFFF;
}

void idt_init() {
  idt_load(&idtp);

  terminal_setcolor(10, 0);
  printf("IDT Loaded\n");
  terminal_setcolor(7, 0);
}

void idt_enableGate(int interrupt) {
  FLAG_SET(idt_entries[interrupt].flags, IDT_FLAG_PRESENT);
}

void idt_disableGate(int interrupt) {
  FLAG_UNSET(idt_entries[interrupt].flags, IDT_FLAG_PRESENT);
}

