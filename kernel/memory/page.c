#include <kernel/page.h>

extern void loadPageDirectory(unsigned int *);
extern void enablePaging();

unsigned int page_directory[1024] __attribute__((aligned(4096)));
unsigned int first_page_table[1024] __attribute__((aligned(4096)));

void paging_init() {
  unsigned int i;

  for (i = 0; i < 1024; i++) {
    page_directory[i] = 0x00000002;
  }

  for (i = 0; i < 1024; i++) {
    first_page_table[i] = (i * 0x1000) | 3;
  }

  page_directory[0] = ((unsigned int)first_page_table) | 3;

  loadPageDirectory(page_directory);
  enablePaging();

  terminal_setcolor(10, 0);
  puts("Paging Enabled");
  terminal_setcolor(7, 0);
}
