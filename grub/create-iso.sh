#!/bin/sh

DATE=`date --date="now" "+%Y-%m-%d"`

cp ../kernel/thoth.bin isodir/boot/thoth.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o thoth.iso isodir
#cp thoth.iso thoth-${DATE}.iso
