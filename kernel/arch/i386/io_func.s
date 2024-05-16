.intel_syntax noprefix
.section .text

.global EnableInterrupts
EnableInterrupts:
  sti
  ret

.global DisableInterrutps
DisableInterrutps:
  cli
  ret

.global crasher
crasher:
  int 0x80
  ret
