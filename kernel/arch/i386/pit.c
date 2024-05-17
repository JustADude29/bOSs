#include <kernel/pit.h>

#define CHANNEL1_DATA_REGISTER 0x40
#define CHANNEL2_DATA_REGISTER 0x41
#define CHANNEL3_DATA_REGISTER 0x42

#define CHANNELS_COMMAND_REGISTER 0x43

void set_timer_phase(int hz) {
  timer_freq = hz;
  int divisor = 1193180 / hz;
  outportb(CHANNELS_COMMAND_REGISTER, 0x36);
  outportb(CHANNEL1_DATA_REGISTER, divisor & 0xFF);
  outportb(CHANNEL1_DATA_REGISTER, divisor >> 8);
}

void timer_handler(registers *r) {
  timer_ticks++;

  if (timer_ticks % timer_freq == 0) {
    printf(".");
  }
}

void timer_init() { 
  irq_install_handler(0, timer_handler); 
  terminal_setcolor(10, 0);
  printf("PIT Loaded\n");
  terminal_setcolor(7, 0);
}
