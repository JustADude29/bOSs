#ifndef _KERNEL_ISRS
#define _KERNEL_ISRS

#include <stdio.h>
#include <string.h>

struct regs {
  unsigned int ds; /* pushed the segs last */
  unsigned int edi, esi, ebp, kernelesp, ebx, edx, ecx,
      eax;                       /* pushed by 'pusha' */
  unsigned int int_no, err_code; /* our 'push byte #' and ecodes do this */
  unsigned int eip, cs, eflags, useresp,
      ss; /* pushed by the processor automatically */
} __attribute__((packed));

typedef void (*ISRHandler)(struct regs *r);

void isrs_init();

void fault_handler(struct regs *r);

void isr_register_handler(int interrupt, void (*handler)(struct regs *r));

#endif // !_KERNEL_ISRS
