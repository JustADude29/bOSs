#include "hal.h"

void hal_init() {
  terminal_initialize();
  gdt_init();
  idt_init();
  isrs_init();
  irq_init();
  paging_init();
  timer_init();
  keyboard_init();
}

void hal_detect_memory(multiboot_info_t *mbd, unsigned int magic) {
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    panic("invalid magic number!");
    return;
  }

  if (!(mbd->flags >> 6 & 0x1)) {
    panic("invalid memory map given by GRUB bootloader");
    return;
  }

  for (int i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)) {
    multiboot_memory_map_t *mmmt =
        (multiboot_memory_map_t *)(mbd->mmap_addr + i);

    printf("Start Addr: 0x%lx | Length: %lu | Size: %d | Type: %d\n",
           mmmt->addr, mmmt->len, mmmt->size, mmmt->type);

    if (mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
      printf("Memory available!\n");
    }
  }
}
