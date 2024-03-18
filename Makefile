ASM=i686-elf-as
GCC=i686-elf-gcc
LD=i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

all: myos.iso

bin/boot.o: src/boot.s
	$(ASM) src/boot.s -o bin/boot.o

bin/kernel.o: src/kernel.c
	$(GCC) -c src/kernel.c -o bin/kernel.o $(CFLAGS)

bin/myos.bin: bin/boot.o bin/kernel.o
	$(LD) -T src/linker.ld -o bin/myos.bin bin/boot.o bin/kernel.o $(LDFLAGS)

copyFiles:
	mkdir -p mkdir -p isodir/boot/grub
	cp bin/myos.bin isodir/boot/myos.bin
	cp src/grub.cfg isodir/boot/grub/grub.cfg

myos.iso: bin/myos.bin copyFiles
	grub2-mkrescue -o myos.iso isodir

clean:
	rm -rf bin/*
	rm -f myos.iso

test: myos.iso
	qemu-system-i386 -cdrom myos.iso	

.PHONY: all clean

