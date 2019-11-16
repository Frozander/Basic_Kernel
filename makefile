CC = ~/opt/cross/bin/i686-elf-gcc
C_FLAGS = -std=gnu99 -ffreestanding -g -c
C_LINKER_FLAGS = -ffreestanding -nostdlib -g -lgcc -T linker.ld

BUILD_DIR = ./out
_BUILD =  mykernel.elf

OBJ_DIR = ./int
_OBJ = kernel.o start.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

DEPS = colours.h

$(OBJ_DIR)/%.o: %.c $(DEPS)
	@mkdir -p $(@D)
	$(CC) $(C_FLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.s
	@mkdir -p $(@D)
	$(CC) $(C_FLAGS) $< -o $@

build_kernel: $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(C_LINKER_FLAGS) $^ -o $(BUILD_DIR)/mykernel.elf
	echo "qemu-system-i386 -kernel mykernel.elf" > ./out/kernel_start.bat

clean:
	rm -rf $(OBJ_DIR)/*.o $(BUILD_DIR)/*

all: build_kernel
.PHONY: clean

