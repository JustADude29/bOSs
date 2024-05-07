.intel_syntax noprefix
.section .text
	.global gdt_load

gdt_load:
	# Load the new GDT by dereferencing the pointer contained
	# in register eax, which points to the 48 bit struct.
	lgdt [eax]
	
	# Set the data segment registers
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	# Jump to flush
	jmp flush

flush:
	ret
