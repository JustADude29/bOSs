#include <kernel/idt.h>
#include <kernel/isrs.h>
#include <kernel/tty.h>

#define MODULE          "ISR"

ISRHandler ISRHandlers[256];

void isrs_init_gates();

void isrs_init() {
  isrs_init_gates();

  for(int i=0; i<256; i++) {
    idt_enableGate(i);
  }
  idt_disableGate(0x80);

  terminal_setcolor(10, 0);
  printf("ISRs Loaded\n");
  terminal_setcolor(7, 0);
}


void fault_handler(registers *r) {
  terminal_setcolor(4, 0);
  if(ISRHandlers[r->int_no] != NULL){
    ISRHandlers[r->int_no](r);
  }
  else if (r->int_no < 32) {
    printf("\n%s encountered:\n", isr_exceptions[r->int_no]);
    printf("  eax:%x ebx:%x ecx:%x edx:%x esi:%x edi:%x\n", r->eax, r->ebx,
           r->ecx, r->edx, r->esi, r->edi);
    printf("  esp:%x ebp:%x eip:%x eflags:%x cs:%x ds:%x ss:%x\n", r->kernelesp,
           r->ebp, r->eip, r->eflags, r->cs, r->ds, r->ss);
    printf("  Interrupt: %x ErrorCode: %x\n", r->int_no, r->err_code);
    printf("SYSTEM HALTED!\n");
    for (;;)
      ;
  } else {
    puts("Unhandled Exception encountered:");
    printf("  eax:%x ebx:%x ecx:%x edx:%x esi:%x edi:%x\n", r->eax, r->ebx,
           r->ecx, r->edx, r->esi, r->edi);
    printf("  esp:%x ebp:%x eip:%x eflags:%x cs:%x ds:%x ss:%x\n", r->kernelesp,
           r->ebp, r->eip, r->eflags, r->cs, r->ds, r->ss);
    printf("  Interrupt: %x ErrorCode: %x\n", r->int_no, r->err_code);
  }
  terminal_setcolor(7, 0);
}

void isr_register_handler(int interrupt, void (*handler)(registers *r)) {
  ISRHandlers[interrupt] = handler;
  idt_enableGate(interrupt);
}

void isr_list_handlers() {
  for(int i=32; i<256; i++) {
    if(ISRHandlers[i]!=NULL)
      printf("Yooo\n");
  }
}
