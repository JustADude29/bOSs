.intel_syntax noprefix
.section .text
.global gdt_load

gdt_load:
	# Load the new GDT by dereferencing the pointer contained
	# in register eax, which points to the 48 bit struct.
  mov eax, [esp+4]
	lgdt [eax]
	
	# Set the data segment registers
	mov eax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	# Jump to flush
	jmp 0x08:flush

flush:
	ret
