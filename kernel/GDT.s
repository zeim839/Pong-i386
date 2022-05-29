.text
.globl loadGDTP
.globl loadIDT
.globl GDT_NULL_DESCRIPTOR
.globl GDT_CODE
.globl GDT_DATA
.globl GDT_DESC

GDT_NULL_DESCRIPTOR:
    .long    0x0
    .long    0x0
GDT_CODE:
    .word    0xffff
    .word    0x0
    .byte    0x0
    .byte    0x9A
    .byte    0xCF
    .byte    0x0
GDT_DATA:
    .word    0xffff
    .word    0x0
    .byte    0x0
    .byte    0x92
    .byte    0xCF
    .byte    0x0
GDT_DESC:
    .word      (GDT_DESC - GDT_NULL_DESCRIPTOR - 1)
    .long      GDT_NULL_DESCRIPTOR

loadGDTP:
    /* Load GDT. Segments will have to be reloaded before
    actually taking effect. */
    lgdt    GDT_DESC

    /* Performing a far jump to the code segment instructs 
    the CPU to reload the CS segment register. */
    ljmp    $(GDT_CODE - GDT_NULL_DESCRIPTOR), $.reload_CS
    
    .reload_CS:
        /* The rest of the segment registers can be reloaded
        by directly changing their value. */
        mov   $(GDT_DATA - GDT_NULL_DESCRIPTOR), %ax
        mov   %ax, %ds 
        mov   %ax, %es
        mov   %ax, %fs
        mov   %ax, %gs
        mov   %ax, %ss

    ret
