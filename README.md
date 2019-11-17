# Basic Kernel Project
It has OS in its name, even though it is just a crappy kernel.  
Deal with it.

## Building
Needs a cross-compiler.  
Makefile uses gcc so you need to compile latest *binutils* and *gcc* for i686 target.  
Just call "make" to build and call "clean" to remove output files.

## How to Run
Since this is a i386 kernel, you need a hardware based on that architecture. So you might need that.  

If you want to install it on your hardware (which I advise you not to), add the kernel elf file to your GRUB.

And for a simpler and safer testing, just use QEMU. there is a .bat script in the "out" folder. If you are on linux just change the file extension to .sh and run it in bash.

## What it does?
Pretty much nothing. The kernel only has basic ASCII text and VGA textmode colours.