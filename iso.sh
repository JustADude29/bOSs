#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/bOSs.kernel isodir/boot/bOSs.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "bOSs" {
	multiboot /boot/bOSs.kernel
}
EOF
grub2-mkrescue -o bOSs.iso isodir
