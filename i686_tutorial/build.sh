i686-elf-as boot.s -o boot.o
i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

if grub-file --is-x86-multiboot myos.bin; then
    echo multiboot confirmed
else
    echo the file is not multiboot!
fi


cp myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir

export DISPLAY=:0; nohup frain_breeze &>/dev/null & #to open qemu on host machine, instead of in the console we're running it from (cuz ssh is weird)
qemu-system-i386 -cdrom myos.iso
