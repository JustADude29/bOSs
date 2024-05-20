#include <kernel/page.h>

extern void loadPageDirectory(unsigned int *);
extern void enablePaging();

uint64_t page_dir_ptr_table[512] __attribute__((aligned(0x20)));
uint64_t page_dir[512] __attribute__((aligned(4096)));

void paging_init() {
  // unsigned int i;
  //
  // for (i = 0; i < 1024; i++) {
  //   page_directory[i] = 0x00000002;
  // }
  //
  // for (i = 0; i < 1024; i++) {
  //   first_page_table[i] = (i * 0x1000) | 3;
  // }
  page_dir_ptr_table[0] = (uint64_t)&page_dir | 1;
  page_dir[0] = 0b10000011; //Address=0, 2MIB, RW and present
  // page_directory[0] = ((unsigned int)first_page_table) | 3;

  // loadPageDirectory(page_directory);
  // enablePaging();
  asm volatile ("movl %%cr4, %%eax; bts $5, %%eax; movl %%eax, %%cr4" ::: "eax"); // set bit5 in CR4 to enable PAE		 
  asm volatile ("movl %0, %%cr3" :: "r" (&page_dir_ptr_table)); // load PDPT into CR3

  asm volatile ("movl %%cr0, %%eax; orl $0x80000000, %%eax; movl %%eax, %%cr0;" ::: "eax"); // enable paging

  terminal_setcolor(10, 0);
  puts("Paging Enabled");
  terminal_setcolor(7, 0);
}
