mkdir -p int out

# Create object files
~/opt/cross/bin/i686-elf-gcc -std=gnu99 -ffreestanding -g -c start.s -o ./int/start.o
~/opt/cross/bin/i686-elf-gcc -std=gnu99 -ffreestanding -g -c kernel.c -o ./int/kernel.o
# Linking
~/opt/cross/bin/i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld ./int/start.o ./int/kernel.o -o ./out/mykernel.elf -lgcc

echo "qemu-system-i386 -kernel mykernel.elf" > ./out/kernel_start.bat