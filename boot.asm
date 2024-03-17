[org 0x7c00]
characters: 
	cmp bx, 258
	je end
	mov ah, 0
	int 0x16
	mov ah, 0x0e
    cmp al, 8
    je back
	mov [bx], al
	int 0x10
	inc bx
	jmp characters
back:
    int 0x10
    mov al, ' '
    int 0x10
    mov al, 0
    mov [buffer + bx], al
    dec bx
    jmp characters
end:
	jmp $
buffer:
	times 258 db 0
	mov bx, buffer
times 510-($-$$) db 0
db 0x55, 0xaa 
