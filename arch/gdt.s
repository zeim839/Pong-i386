.text
  .globl  load_gdt
  .globl  CODE_SEL
  .globl  DATA_SEL

/* This is a replica of the default GRUB GDT. We don't
care about the specifics of segment descriptors, we just
need access to GDT and descriptor memory addresses.*/
GDT:
NULL_SEG:
  .word	  0, 0
	.byte	  0, 0, 0, 0
CODE_SEG:
  .word	  0xFFFF, 0
	.byte	  0, 0x9A, 0xCF, 0
DATA_SEG:
  .word 	0xFFFF, 0
	.byte	  0, 0x92, 0xCF, 0

GDT_DESC:
  .word	  0x27			/* limit */
  .long	  GDT			  /* addr */

/* Logical address of code segment with respect
to GDT table .*/
CODE_SEL:
  .word   (CODE_SEG - NULL_SEG)

/* Logical address of data segment with respect
to GDT table */
DATA_SEL:
  .word   (DATA_SEG - NULL_SEG)

/* Loads the GDT descriptor, performs far jump
and resets segment registers. */
load_gdt:
  lgdtl	  GDT_DESC

  /* Performing a far jump to the code segment instructs
  the CPU to reload the CS segment register. */
  ljmp    $(CODE_SEG - NULL_SEG), $.reload_CS

  .reload_CS:
    /* The rest of the segment registers can be reloaded
    by directly changing their value. */
    mov   $(DATA_SEG - NULL_SEG), %ax
    mov   %ax, %ds
    mov   %ax, %es
    mov   %ax, %fs
    mov   %ax, %gs
    mov   %ax, %ss

  ret

