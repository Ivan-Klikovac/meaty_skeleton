#!/bin/sh
set -e
. ./build.sh

mkdir -p iso
mkdir -p iso/boot
mkdir -p iso/boot/grub

cp sysroot/boot/meaty_skeleton.kernel iso/boot/meaty_skeleton.kernel
cat > iso/boot/grub/grub.cfg << EOF
menuentry "Meaty Skeleton" {
	multiboot /boot/meaty_skeleton.kernel
}
EOF
grub-mkrescue -o meaty_skeleton.iso iso
