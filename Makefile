ASM=i686-elf-as
GCC=i686-elf-gcc
LD=i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

all: bOSs.iso

bin/boot.o: src/boot.s
	mkdir -p bin
	$(ASM) src/boot.s -o bin/boot.o

bin/kernel.o: src/kernel.c
	$(GCC) -c src/kernel.c -o bin/kernel.o $(CFLAGS)

bin/bOSs.bin: bin/boot.o bin/kernel.o
	$(LD) -T src/linker.ld -o bin/bOSs.bin bin/boot.o bin/kernel.o $(LDFLAGS)

copyFiles:
	mkdir -p isodir/boot/grub
	cp bin/bOSs.bin isodir/boot/bOSs.bin
	cp src/grub.cfg isodir/boot/grub/grub.cfg

bOSs.iso: bin/bOSs.bin copyFiles
	grub2-mkrescue -o bOSs.iso isodir

clean:
	rm -rf bin/*
	rm -f bOSs.iso

test:
	qemu-system-i386 -cdrom bOSs.iso	

.PHONY: all clean

