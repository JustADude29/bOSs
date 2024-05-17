.intel_syntax noprefix
.section .text

.global idt_load
#.extern idtp

#idt_load:
#  lidt [idtp]
#  ret

idt_load:
  push ebp
  mov ebp, esp

  mov eax, [ebp + 8]
  lidt [eax]

  mov esp, ebp
  pop ebp
  ret
