default:
	$P/i686-elf-as boot.s -o build/boot.o
	$P/i686-elf-as arch/gdt.s -o build/gdt.o
	$P/i686-elf-as arch/isr.s -o build/isr.o
	$P/i686-elf-gcc -c arch/interrupts.c -o build/interrupts.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions
	$P/i686-elf-gcc -c graphics/windows.c -o build/windows.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions
	$P/i686-elf-gcc -c arch/ports.c -o build/ports.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions
	$P/i686-elf-gcc -c drivers/textmode.c -o build/textmode.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions
	$P/i686-elf-gcc -c drivers/clock.c -o build/clock.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions
	$P/i686-elf-gcc -c drivers/pckbrd.c -o build/pckbrd.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions
	$P/i686-elf-gcc -c graphics/assets.c -o build/assets.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions
	$P/i686-elf-gcc -c kernel.c -o build/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions
	$P/i686-elf-gcc -T config/linker.ld -o isodir/boot/Pong-i386.bin -ffreestanding -O2 -nostdlib build/assets.o build/textmode.o build/pckbrd.o build/clock.o build/ports.o build/windows.o build/kernel.o build/isr.o build/interrupts.o build/boot.o build/gdt.o -lgcc

image:
	cp config/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o Pong-i386.iso isodir
