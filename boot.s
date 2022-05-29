.set ALIGN,    1<<0                 /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1                 /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO      /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002           /* 'magic number' lets bootloader find the header */

.set CHECKSUM, -(MAGIC + FLAGS)     /* checksum of above, prevents code from accidentally 
                                       being loaded as kernel */

/*
Implements the multiboot standard
GRUB looks for this when bootloading.
*/
.section .multiboot
    .align  4
    .long   MAGIC
    .long   FLAGS
    .long   CHECKSUM
 
/* Stack */
.section .bss
    .align  16
    stack_bottom:
        .skip   16384 # 16 KiB
    stack_top:
 
.text
.globl _start
.globl _hang
.globl _initStack

/* 
_start is the designated function signature
for starting the kernel via GRUB. 
*/
_start:
    /* GRUB does not initialize the stack, must
    be done manually. */
    mov     $stack_top, %esp

	call    kernelEntry

    /* Do nothing.Prevents the kernel from stopping 
    abruptly. */
    cli
1:	hlt
	jmp 1b

.size _start, . - _start
