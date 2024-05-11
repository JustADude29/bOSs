#ifndef _KERNEL_ISRS
#define _KERNEL_ISRS

#include <stdio.h>
#include <string.h>

struct regs {
  unsigned int gs, fs, es, ds; /* pushed the segs last */
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by 'pusha' */
  unsigned int int_no, err_code; /* our 'push byte #' and ecodes do this */
  unsigned int eip, cs, eflags, useresp,
      ss; /* pushed by the processor automatically */
};

void tester();

void isrs_init();

void fault_handler(struct regs *r);

#endif // !_KERNEL_ISRS
