mov ah, 0x0e
mov al, 'A'
int 0x10

low:
    inc al
    cmp al, 'Z'+1
    je exit
    cmp al, 'a'
    jl lower
    int 0x10
    jmp upp

lower:
    add al, 32
    int 0x10
    jmp upp

upp:
    inc al
    cmp al, 'z'+1
    je exit
    cmp al, 'a'
    jg upper
    int 0x10
    jmp low

upper:
    add al, -32
    int 0x10
    jmp low

exit:
    jmp $

times 510-($-$$) db 0
db 0x55, 0xaa
