#include <kernel/idt.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

extern void idt_load();

struct idt_entry idt_entries[256];
struct idt_ptr idtp;

void set_idt_gate(unsigned int num, unsigned int base, unsigned short sel,
                  unsigned char flags) {
  idt_entries[num].redundant = 0;
  idt_entries[num].flags = flags;
  idt_entries[num].sel = sel;

  idt_entries[num].base_low = (base & 0xFFFF);
  idt_entries[num].base_high = (base >> 16) & 0xFFFF;
}

void idt_init() {
  idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
  idtp.base = &idt_entries;

  memset(&idt_entries, 0, sizeof(struct idt_entry) * 256);

  idt_load();
  printf("IDT loaded\n");
}
