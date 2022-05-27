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
 
.section .text
.globl _start
.globl _hang
.globl _initStack

/* 
_start is the designated function signature
for starting the kernel via GRUB. 
*/
_start:
    call    _initStack
	call    kernelEntry
    call    _hang

/*
Do nothing.
Prevents the kernel from stopping abruptly.
*/
_hang:
    cli
1:	hlt
	jmp 1b

/*
GRUB does not initialize the stack, must
be done manually.
*/
_initStack:
    mov     $stack_top, %esp
    ret

.size _start, . - _start