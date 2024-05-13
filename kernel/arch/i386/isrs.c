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

const char *isr_exceptions[] = {
    // 0 Division by zero:
    "Division by zero",
    // 1 Debug Exception:
    "Debug Exception",
    // 2 Non Maskable Interrupt Exception:
    "Non Maskable Interrupt Exception",
    // 3 Breakpoint Exception:
    "Breakpoint Exception",
    // 4 Overflow Exception:
    "Overflow Exception",
    // 5 Bound Range Exceeded Exception:
    "Bound Range Exceeded Exception",
    // 6 Invalid Opcode Exception:
    "Invalid Opcode Exception",
    // 7 Device Not Available Exception:
    "Device Not Available Exception",
    // 8 Double Fault Exception:
    "Double Fault Exception",
    // 9 Coprocessor Segment Overrun:
    "Coprocessor Segment Overrun",
    // 10 Invalid TSS Exception:
    "Invalid TSS Exception",
    // 11 Segment Not Present:
    "Segment Not Present",
    // 12 Stack-Segment Fault:
    "Stack-Segment Fault",
    // 13 General Protection Fault:
    "General Protection Fault",
    // 14 Page Fault:
    "Page Fault",
    // 15 Reserved:
    "Reserved",
    // 16 x87 Floating-Point Exception:
    "x87 Floating-Point Exception",
    // 17 Alignment Check Exception:
    "Alignment Check Exception",
    // 18 Machine Check Exception:
    "Machine Check Exception",
    // 19 SIMD Floating-Point Exception:
    "SIMD Floating-Point Exception",
    // 20 Virtualization Exception:
    "Virtualization Exception",
    // 21-27: Reserved.
    "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved",
    // 28 Hypervisor Injection Exception
    "Hypervisor Injection Exception",
    // 29 VMM Communication Exception
    "VMM Communication Exception",
    // 30 Security Exception
    "Security Exception",
    // 31 Reserved
    "Reserved"};

void fault_handler(struct regs *r) {
  terminal_setcolor(4, 0);
  if (r->int_no < 32) {
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
    printf("SYSTEM HALTED!\n");
    for (;;)
      ;
  }
  terminal_setcolor(7, 0);
}

void isr_register_handler(int interrupt, void (*handler)(struct regs *r)) {
  ISRHandlers[interrupt] = handler;
  idt_enableGate(interrupt);
}
