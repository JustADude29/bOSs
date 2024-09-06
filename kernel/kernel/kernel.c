#include <stdio.h>

#include <hal.h>

void kernel_main() {
  hal_init();
  
  printf("\nHello bOSs\nKaise Ho aap?\n");
}
