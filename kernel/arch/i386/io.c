#include <kernel/io.h>

unsigned char inportb(unsigned short _port) {
  unsigned char ret;
  __asm__ volatile("inb %w1, %b0" : "=a"(ret) : "Nd"(_port) : "memory");
  return ret;
}

void outportb(unsigned short _port, unsigned char _data) {
  __asm__ volatile("outb %b0, %w1" : : "a"(_data), "Nd"(_port) : "memory");
}

void iowait() { outportb(0x80, 0); }

void panic(char *error) {
  terminal_setcolor(4, 0);
  puts(error);
  terminal_setcolor(7, 0);
}
