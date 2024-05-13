.intel_syntax noprefix
.section .text

.global inportb
inportb:
  mov dx, [esp+4]
  mov al, [esp+8]
  out dx, al
  ret

.global outportb
outportb:
  mov dx, [esp+4]
  xor eax, eax
  in al, dx
  ret

.global EnableInterrupts
EnableInterrupts:
  sti
  ret

.global DisableInterrutps
DisableInterrutps:
  cli
  ret
