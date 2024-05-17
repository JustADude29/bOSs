#include <kernel/io.h>
#include <kernel/pic.h>

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

enum {
  PIC_ICW1_ICW4 = 0x01,
  PIC_ICW1_SINGLE = 0x02,
  PIC_ICW1_INTERVAL4 = 0x04,
  PIC_ICW1_LEVEL = 0x08,
  PIC_ICW1_INITIALIZE = 0x10
} PIC_ICW1;

enum {
  PIC_ICW4_8086 = 0x1,
  PIC_ICW4_AUTO_EOI = 0x2,
  PIC_ICW4_BUFFER_MASTER = 0x4,
  PIC_ICW4_BUFFER_SLAVE = 0x0,
  PIC_ICW4_BUFFERRED = 0x8,
  PIC_ICW4_SFNM = 0x10,
} PIC_ICW4;

enum {
  PIC_CMD_END_OF_INTERRUPT = 0x20,
  PIC_CMD_READ_IRR = 0x0A,
  PIC_CMD_READ_ISR = 0x0B,
} PIC_CMD;

void PIC_Configure(unsigned char offsetPIC1, unsigned char offsetPIC2) {
  outportb(PIC1_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INITIALIZE);
  iowait();
  outportb(PIC2_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INITIALIZE);
  iowait();

  outportb(PIC1_DATA_PORT, offsetPIC1);
  iowait();
  outportb(PIC2_DATA_PORT, offsetPIC2);
  iowait();

  outportb(PIC1_DATA_PORT, 0x4);
  iowait();
  outportb(PIC2_DATA_PORT, 0x2);
  iowait();

  outportb(PIC1_DATA_PORT, PIC_ICW4_8086);
  iowait();
  outportb(PIC2_DATA_PORT, PIC_ICW4_8086);
  iowait();

  outportb(PIC1_DATA_PORT, 0x0);
  iowait();
  outportb(PIC2_DATA_PORT, 0x0);
  iowait();
}

void PIC_SendEndOfInterrupt(int irq) {
  if (irq >= 8)
    outportb(PIC2_COMMAND_PORT, PIC_CMD_END_OF_INTERRUPT);
  outportb(PIC1_COMMAND_PORT, PIC_CMD_END_OF_INTERRUPT);
}

void PIC_Disable() {
  outportb(PIC1_DATA_PORT, 0xFF);
  iowait();
  outportb(PIC2_DATA_PORT, 0xFF);
  iowait();
}

void PIC_Mask(int irq) {
  unsigned char port;

  if (irq < 8) {
    port = PIC1_DATA_PORT;
  } else {
    irq -= 8;
    port = PIC2_DATA_PORT;
  }

  unsigned char mask = inportb(port) | (1 << irq);
  outportb(port, mask);
}

void PIC_Unmask(int irq) {
  unsigned char port;

  if (irq < 8) {
    port = PIC1_DATA_PORT;
  } else {
    irq -= 8;
    port = PIC2_DATA_PORT;
  }

  unsigned char mask = inportb(port) & ~(1 << irq);
  outportb(port, mask);
}

unsigned short PIC_ReadIrqRequestRegister() {
  outportb(PIC1_COMMAND_PORT, PIC_CMD_READ_IRR);
  outportb(PIC2_COMMAND_PORT, PIC_CMD_READ_IRR);
  return ((unsigned short)inportb(PIC2_COMMAND_PORT) |
          ((unsigned short)inportb(PIC2_COMMAND_PORT) << 8));
}

unsigned short PIC_ReadInServiceRegister() {
  outportb(PIC1_COMMAND_PORT, PIC_CMD_READ_ISR);
  outportb(PIC2_COMMAND_PORT, PIC_CMD_READ_ISR);
  return ((unsigned short)inportb(PIC2_COMMAND_PORT) |
          ((unsigned short)inportb(PIC2_COMMAND_PORT) 
          < 8));
}
