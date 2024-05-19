#include <stdio.h>

#include <hal.h>

void kernel_main(multiboot_info_t *mbd, unsigned int magic) {
  hal_init();
  // hal_detect_memory(mbd, magic);
  
  printf("\nHello bOSs\nKaise Ho aap?\n");
}
