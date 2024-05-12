.intel_syntax noprefix
.section .text

.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31


# 0 Division by zero:
isr0:
  cli
  push 0
  push 0
  jmp isr_common_stub

# 1 Debug Exception:
isr1:
  cli
  push 0
  push 1
  jmp isr_common_stub

# 2 Non Maskable Interrup Exception:
isr2:
  cli
  push 0
  push 2
  jmp isr_common_stub

# 3 Breakpoint Exception:
isr3:
  cli
  push 0
  push 3
  jmp isr_common_stub

# 4 Overflow Exception:
isr4:
  cli
  push 0
  push 4
  jmp isr_common_stub

# 5 Bound Range Exceeded Exception:
isr5:
  cli
  push 0
  push 5
  jmp isr_common_stub

# 6 Invalid Opcode Exception:
isr6:
  cli
  push 0
  push 6
  jmp isr_common_stub

# 7 No Coprocessor Exception:
isr7:
  cli
  push 0
  push 8
  jmp isr_common_stub

# 8 Double Fault Exception:
isr8:
  cli
  push 8
  jmp isr_common_stub

# 9 Coprocessor Segment Overrun:
isr9:
  cli
  push 0
  push 9
  jmp isr_common_stub

# 10 Invalid TSS Exception:
isr10:
  cli
  push 10
  jmp isr_common_stub

# 11 Segment Not Present:
isr11:
  cli
  push 11
  jmp isr_common_stub

# 12 Stack-Segment Fault:
isr12:
  cli
  push 12
  jmp isr_common_stub

# 13 General Protection Fault:
isr13:
  cli
  push 13
  jmp isr_common_stub

# 14 Page Fault:
isr14:
  cli
  push 14
  jmp isr_common_stub

# 15 Reserved:
isr15:
  cli
  push 0
  push 15
  jmp isr_common_stub

# 16 x87 Floating-Point Exception:
isr16:
  cli
  push 0
  push 16
  jmp isr_common_stub

# 17 Alignment Check Exception:
isr17:
  cli
  push 17
  jmp isr_common_stub

# 18 Machine Check Exception:
isr18:
  cli
  push 0
  push 18
  jmp isr_common_stub

# 19 SIMD Floating-Point Exception:
isr19:
  cli
  push 0
  push 19
  jmp isr_common_stub

# 20 Virtualization Exception:
isr20:
  cli
  push 0
  push 20
  jmp isr_common_stub

# 21-31: Reserved for Intel, typically not used.
isr21:
  cli
  push 21
  jmp isr_common_stub

isr22:
  cli
  push 0
  push 22
  jmp isr_common_stub

isr23:
  cli
  push 0
  push 23
  jmp isr_common_stub

isr24:
  cli
  push 0
  push 24
  jmp isr_common_stub

isr25:
  cli
  push 0
  push 25
  jmp isr_common_stub

isr26:
  cli
  push 0
  push 26
  jmp isr_common_stub

isr27:
  cli
  push 0
  push 27
  jmp isr_common_stub

isr28:
  cli
  push 0
  push 28
  jmp isr_common_stub

isr29:
  cli
  push 29
  jmp isr_common_stub

isr30:
  cli
  push 30
  jmp isr_common_stub

isr31:
  cli
  push 0
  push 31
  jmp isr_common_stub

# --------------------------------------------
.extern fault_handler

# Common ISR stub
isr_common_stub:
  pusha

  xor eax, eax
  mov ax, ds
  push eax

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  push esp
  call fault_handler
  add esp, 4

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa
  add esp, 8
  iret

