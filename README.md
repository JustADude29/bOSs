# bOSs

bOSs is currently a barebones OS that does nothing, dont waste your time on it

## Requirements:

- [i686-elf toolchain](https://wiki.osdev.org/GCC_Cross-Compiler)
- [Grub2](https://www.gnu.org/software/grub/grub-download.html) and [Xorriso](https://www.gnu.org/software/xorriso/)
- [GNU Make](https://www.gnu.org/software/make/)
- [Qemu](https://www.qemu.org/download/)

## Building and Running:

- Run `make build` to build the kernel and libc libraries
- Run `make iso` to make iso
- Run `make run` to run the iso on qemu
- Run `make clean` to clean

## Milestones:
- [x] Standard Library
- [x] Terminal Printing
- [x] Implement GDT
- [x] Interrupts:
    - [x] CPU Interrupts
    - [x] Hardware Interrupts
- [x] Timer
- [x] Keyboard Input
- [-] Paging:
    - [x] Simple Non-PAE paging
    - ~~[x] PAE~~ (Will Merge if needed later)
    - [ ] Page Allocator
- [ ] Permissions
