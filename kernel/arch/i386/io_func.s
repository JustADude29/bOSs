.intel_syntax noprefix
.section .text

.global EnableInterrupts
EnableInterrupts:
  sti
  ret

.global DisableInterrupts
DisableInterrupts:
  cli
  ret

.global crasher
crasher:
  int 0x80
  ret
