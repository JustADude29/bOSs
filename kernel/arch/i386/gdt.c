#include <kernel/gdt.h>
#include <stdint.h>
#include <stdio.h>

extern void gdt_load(addr_t);

struct gdt_entry gdt_entries[5];
struct gdt_ptr GDTStruct;

void gdt_init() {
  GDTStruct.limit = (sizeof(struct gdt_entry)*5) - 1;
  GDTStruct.base = &gdt_entries;
  
  set_gdt_gate(0, 0, 0, 0, 0);  // null segment
  set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // kernel code
  set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // kernel data
  set_gdt_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // user code 
  set_gdt_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // user data

  gdt_load(&GDTStruct);
}

void set_gdt_gate(unsigned int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran){
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;

  gdt_entries[num].limit = (limit & 0xFFFF);
  gdt_entries[num].flags = (limit >> 16) & 0x0F;
  gdt_entries[num].flags |= (gran & 0xF0);

  gdt_entries[num].access = access;
}
