#include <stdio.h>

#include <kernel/irq.h>
#include <kernel/io.h>
#include <kernel/pic.h>

#define PIC_REMAP_OFFSET 0x20

IRQHandler irq_handlers[16];

void IRQ_Handler(struct regs *r) {
  int irq = r->int_no - PIC_REMAP_OFFSET;

  unsigned short pic_isr = PIC_ReadInServiceRegister();
  unsigned short pic_irr = PIC_ReadIrqRequestRegister();

  if(irq_handlers[irq] != NULL) {
    irq_handlers[irq](r);
  } else {
    printf("Unhandled IRQ: %d, ISR: %x, IRR: %x\n", irq, pic_isr, pic_irr);
  }

  PIC_SendEndOfInterrupt(irq);
}

void irq_init() {
  PIC_Configure(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET+8);

  for(int i=0; i<16; i++) {
    isr_register_handler(PIC_REMAP_OFFSET + i, IRQ_Handler);
  }

  EnableInterrupts();

  terminal_setcolor(10, 0);
  printf("IRQ Loaded\n");
  terminal_setcolor(7, 0);
}

void irq_install_handler(int irq, IRQHandler handler) {
  irq_handlers[irq] = handler;
}
