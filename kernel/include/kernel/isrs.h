#ifndef _KERNEL_ISRS
#define _KERNEL_ISRS

#include <stdio.h>
#include <string.h>

typedef struct {
  unsigned int ds; /* pushed the segs last */
  unsigned int edi, esi, ebp, kernelesp, ebx, edx, ecx,
      eax;                       /* pushed by 'pusha' */
  unsigned int int_no, err_code; /* our 'push byte #' and ecodes do this */
  unsigned int eip, cs, eflags, useresp,
      ss; /* pushed by the processor automatically */
} __attribute__((packed)) registers;

typedef void (*ISRHandler)(registers *r);

void isrs_init();

void fault_handler(registers *r);

void isr_register_handler(int interrupt, void (*handler)(registers *r));

static const char *isr_exceptions[] = {
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

#endif // !_KERNEL_ISRS
