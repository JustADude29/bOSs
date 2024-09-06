#include <kernel/page.h>
#include <kernel/multiboot.h>

extern uint32_t endkernel;
extern void loadPageDirectory(unsigned int *);
extern void enablePaging();

multiboot_info_t *multiboot_info;
unsigned int magic_number;

pde_t page_directory[1024] __attribute__((aligned(4096)));
page_t first_page_table[1024] __attribute__((aligned(4096)));

unsigned int free_memory;
uint32_t total_memory;

void paging_init() {
  uint64_t top_addr;
  uint64_t higher_addr = 0;

  free_memory = 0;
  total_memory = 0;

  if (magic_number != MULTIBOOT_BOOTLOADER_MAGIC) {
    panic("invalid magic_number number!");
    return;
  }

  if (!(multiboot_info->flags >> 6 & 0x1)) {
    panic("invalid memory map given by GRUB bootloader");
    return;
  }

  for (int i = 0; i < multiboot_info->mmap_length; i += sizeof(multiboot_memory_map_t)) {
    multiboot_memory_map_t *mmmt =
        (multiboot_memory_map_t *)(multiboot_info->mmap_addr + i);
    total_memory += mmmt->len;

    if (mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
      top_addr = mmmt->addr + mmmt->len;
      if(top_addr > higher_addr)
        higher_addr = top_addr;
      printf("Memory available at address:  %lx, len: %lx, top addr: %lx, higher addr:  %lx\n", 
              top_addr, mmmt->len, top_addr, higher_addr);
      free_memory+=mmmt->len;
    }
  }

  unsigned int i;

  for (i = 0; i < 1024; i++) {
    page_directory[i] = 0x00000001;
  }

  for (i = 0; i < 1024; i++) {
    first_page_table[i] = (i * 0x1000) | 3;
  }

  page_directory[0] = ((unsigned int)first_page_table) | 3;

  loadPageDirectory(page_directory);
  enablePaging();

  terminal_setcolor(10, 0);
  puts("Paging Enabled");
  printf("Free memory: %d mb\n", free_memory/1024/1024);
  printf("Total memory: %x\n", total_memory);
  terminal_setcolor(7, 0);
}
