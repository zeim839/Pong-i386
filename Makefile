CFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions
LFLAGS = -ffreestanding -O2 -nostdlib -lgcc
GCC = $P/i686-elf-gcc
AS = $P/i686-elf-as

C_SOURCES =	kernel.c           \
						arch/ports.c       \
						arch/interrupts.c  \
						drivers/clock.c    \
						drivers/pckbrd.c   \
						drivers/textmode.c \
						graphics/assets.c  \
						graphics/windows.c

ASM_SOURCES =	boot.s     \
							arch/isr.s \
						  arch/gdt.s

default: build-c build-asm
	$(GCC) -T config/linker.ld -o isodir/boot/Pong-i386.bin $(wildcard build/*.o) $(LFLAGS)

image: build-dir
	cp config/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o Pong-i386.iso isodir

build-c: build-dir
	$(foreach SRC, $(C_SOURCES), \
		$(GCC) -c $(SRC) -o build/$(notdir $(SRC:%.c=%.o)) $(CFLAGS) ; )

build-asm: build-dir
	$(foreach SRC, $(ASM_SOURCES), \
		$(AS) $(SRC) -o build/$(notdir $(SRC:%.s=%.o)) ; )

build-dir:
	@mkdir -p build
	@mkdir -p isodir
	@mkdir -p isodir/boot
	@mkdir -p isodir/boot/grub
