.text
  .globl int_handle /* In ../interrupts.h */
  .globl DATA_SEL   /* In ../gdt.s */

  /* Generic handlers, for when we dont care about passing
  specific input to ISR_COMMON, IRQ_COMMON */
  .globl itge_reserved
  .globl irq_unsupported_mstr
  .globl irq_unsupported_slve

  /* Interrupt service routines */
  .globl itge_divide_zero
  .globl itge_debug
  .globl itge_non_mask_int
  .globl itge_breakpoint
  .globl itge_overflow
  .globl itge_bound_exceed
  .globl itge_invalid_op
  .globl itge_device_na
  .globl itge_double_fault
  .globl itge_coproc_seg_overr
  .globl itge_invalid_tss
  .globl itge_segment_na
  .globl itge_ss_fault
  .globl itge_gp_fault
  .globl itge_pg_fault
  .globl itge_float_pt
  .globl itge_align_chk
  .globl itge_mach_chk
  .globl itge_SIMD_float_pt
  .globl itge_virt_exc
  .globl itge_ctrlp_exc

  /* Supported hardware interrupts*/
  .globl irq_timer
  .globl irq_keyboard


/*=============================
       GENERIC HANDLERS
  =============================  */
ISR_COMMON:
	pusha
	mov   %ds, %ax
	push  %eax
	mov   DATA_SEL, %ax
	mov   %ax, %ds
	mov   %ax, %es
	mov   %ax, %fs
	mov   %ax, %gs
	call  int_handle
	pop   %eax
	mov   %ax, %ds
	mov   %ax, %es
	mov   %ax, %fs
	mov   %ax, %gs
	popa
  add   $4, %esp
	sti
	iret

IRQ_COMMON:
	pusha
	mov   %ds, %ax
	push  %eax
	mov   DATA_SEL, %ax
	mov   %ax, %ds
	mov   %ax, %es
	mov   %ax, %fs
	mov   %ax, %gs
	call  int_handle
	pop   %ebx
	mov   %bx, %ds
	mov   %bx, %es
	mov   %bx, %fs
	mov   %bx, %gs
	popa
	add   $4, %esp
	iret


/*=============================
    INTERRUPT GATE ROUTINES
  =============================  */
itge_divide_zero:
  cli
  pushl $0
  jmp  ISR_COMMON

itge_debug:
  cli
  pushl $1
  jmp   ISR_COMMON

itge_non_mask_int:
  cli
  pushl $2
  jmp   ISR_COMMON

itge_breakpoint:
  cli
  pushl $3
  jmp   ISR_COMMON

itge_overflow:
  cli
  pushl $4
  jmp   ISR_COMMON

itge_bound_exceed:
  cli
  pushl $5
  jmp   ISR_COMMON

itge_invalid_op:
  cli
  pushl $6
  jmp   ISR_COMMON

itge_device_na:
  cli
  pushl $7
  jmp   ISR_COMMON

itge_double_fault:
  cli
  pushl $8
  jmp   ISR_COMMON

itge_coproc_seg_overr:
  cli
  pushl $9
  jmp   ISR_COMMON

itge_invalid_tss:
  cli
  pushl $10
  jmp   ISR_COMMON

itge_segment_na:
  cli
  pushl $11
  jmp   ISR_COMMON

itge_ss_fault:
  cli
  pushl $12
  jmp   ISR_COMMON

itge_gp_fault:
  cli
  pushl $13
  jmp   ISR_COMMON

itge_pg_fault:
  cli
  pushl $14
  jmp   ISR_COMMON

itge_float_pt:
  cli
  pushl $15
  jmp   ISR_COMMON

itge_align_chk:
  cli
  pushl $16
  jmp   ISR_COMMON

itge_mach_chk:
  cli
  pushl $17
  jmp   ISR_COMMON

itge_SIMD_float_pt:
  cli
  pushl $18
  jmp   ISR_COMMON

itge_virt_exc:
  cli
  pushl $19
  jmp   ISR_COMMON

itge_ctrlp_exc:
  cli
  pushl $20
  jmp   ISR_COMMON

itge_reserved:
  cli
  pushl $21
  jmp   ISR_COMMON

/*=============================
  HARDWARE INTERRUPT REQUESTS
  =============================  */
irq_timer:
  pushl $32
  jmp   IRQ_COMMON

irq_keyboard:
  pushl $33
  jmp   IRQ_COMMON

irq_unsupported_mstr:
  pushl $34
  jmp   IRQ_COMMON

irq_unsupported_slve:
  pushl $40
  jmp   IRQ_COMMON
