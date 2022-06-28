#include "interrupts.h"

/*=============================
      Basic PIC Driver
  =============================  */
void remap_pic ()
{
  /* Send EOI, reset PIC*/
  outb(PIC_MSTR_CTR_PORT, 0x20);

  outb(PIC_MSTR_CTR_PORT, 0x11);
  outb(PIC_SLVE_CTR_PORT, 0x11);

  /* Remap IRQ gates to 32-40*/
  outb(PIC_MSTR_DAT_PORT, IRQ0_VECTOR);
  outb(PIC_SLVE_DAT_PORT, IRQ8_VECTOR);

  outb(PIC_MSTR_DAT_PORT, 0x04);
  outb(PIC_SLVE_DAT_PORT, 0x02);

  outb(PIC_MSTR_DAT_PORT, 0x01);
  outb(PIC_SLVE_DAT_PORT, 0x01);

  /* Enable all PIC IRQs*/
  outb(PIC_MSTR_DAT_PORT, 0x0);
  outb(PIC_SLVE_DAT_PORT, 0x0);
}

void mask_irq (uint8_t irq)
{
  uint8_t ctl_mask = irq < 8 ? PIC_MSTR_DAT_PORT : PIC_SLVE_DAT_PORT;
 	outb(ctl_mask, inb(ctl_mask) & ~(1 << (irq & 0x7)));
}

void unmask_irq (uint8_t irq)
{
  uint8_t ctl_mask  = irq < 8 ? PIC_MSTR_DAT_PORT : PIC_SLVE_DAT_PORT;
	outb(ctl_mask, inb(ctl_mask) | (1 << (irq & 0x7)));
}

void eoi_master () {
  outb(PIC_MSTR_CTR_PORT, END_OF_INT);
}

void eoi_slave () {
  outb(PIC_SLVE_CTR_PORT, END_OF_INT);
}

/*=============================
   Interrupt Descriptor Table
  =============================  */
struct irq_hook TABLE[256];
struct irq_table TABLE_DESC;

void clear_table ()
{
  /* Casting unnecessary but silences compiler warnings  */
  uint32_t*  ptr = (uint32_t*)&TABLE[0];
  for (size_t i = 0; i<256; i++) {
    *ptr = 0;
    ptr++;
  }
}

void load_IDT()
{
  TABLE_DESC.LIMIT = TABLE_SIZE - 1;
  TABLE_DESC.BASE = (uint32_t) &TABLE[0];
  asm volatile ("lidt %0" : : "m"(TABLE_DESC));
  asm("sti");
}

void init_interrupts ()
{
  remap_pic();
  clear_table();

  /* Hooks in include/isr.h */
  register_hook(0, (uint32_t)&itge_divide_zero);
  register_hook(1, (uint32_t)&itge_debug);
  register_hook(2, (uint32_t)&itge_non_mask_int);
  register_hook(3, (uint32_t)&itge_breakpoint);
  register_hook(4, (uint32_t)&itge_overflow);
  register_hook(5, (uint32_t)&itge_bound_exceed);
  register_hook(6, (uint32_t)&itge_invalid_op);
  register_hook(7, (uint32_t)&itge_device_na);
  register_hook(8, (uint32_t)&itge_double_fault);
  register_hook(9, (uint32_t)&itge_coproc_seg_overr);
  register_hook(10, (uint32_t)&itge_invalid_tss);
  register_hook(11, (uint32_t)&itge_segment_na);
  register_hook(12, (uint32_t)&itge_ss_fault);
  register_hook(13, (uint32_t)&itge_gp_fault);
  register_hook(14, (uint32_t)&itge_pg_fault);
  register_hook(15, (uint32_t)&itge_float_pt);
  register_hook(16, (uint32_t)&itge_align_chk);
  register_hook(17, (uint32_t)&itge_mach_chk);
  register_hook(18, (uint32_t)&itge_SIMD_float_pt);
  register_hook(19, (uint32_t)&itge_virt_exc);
  register_hook(20, (uint32_t)&itge_ctrlp_exc);

  /* Reserved by intel */
  for (size_t i = 21; i < 32; i++)
    register_hook(i, (uint32_t)&itge_reserved);

  /* Hardware */
  register_hook(CLOCK_IRQ, (uint32_t)irq_timer);
  register_hook(KEYBOARD_IRQ, (uint32_t)irq_keyboard);

  for (size_t i = 34; i < 40; i++)
    register_hook(i, (uint32_t)&irq_unsupported_mstr);

  for (size_t i = 40; i < 48; i++)
    register_hook(i, (uint32_t)&irq_unsupported_slve);

  load_IDT();
  inb(0x60);
}

/*=============================
   Interrupt Routine Handlers
  =============================  */

/* Just acknowledge until an actual handler is
registered by drivers.*/
void (*irq_timer_handler)(void) = &eoi_master;
void (*irq_keyboard_handler)(void) = &eoi_master;

void int_handle (struct registers_t registers)
{
  uint32_t intr = registers.INTR;

  /* Ignore the reserved interrupt vectors */
  if (intr > 20 && intr < 32) return;

  /* Print debug message and hang */
  if (intr < 21) {
    unsigned char str[] = "FATAL EXCEPTION";
    println(&str[0]);
    while(1) {}
  }

  /* Timer hardware IRQ. */
  if (intr == 32) {
    (*irq_timer_handler)();
    return;
  }

  /* Keyboard hardware IRQ.  */
  if (intr == 33) {
    (*irq_keyboard_handler)();
    return;
  }

  /* IRQs 34-39 are passed as no. 34. They are acknowledged
  and ignored.*/
  if (intr == 34) {
    eoi_master();
    return;
  }

  /* IRQs 40-47 are passed as no. 40. They are acknowledged
  and ignored. */
  if (intr == 40) {
    eoi_slave();
    eoi_master();
    return;
  }
}

void init_timer(void* base) {
  irq_timer_handler = base;
}

void init_keyboard(void* base) {
  irq_keyboard_handler = base;
}

void register_hook(size_t vector, uint32_t ptr)
{
  TABLE[vector].BASE_LOW   = (unsigned short)(ptr & 0xFFFF);
  TABLE[vector].SEL        = (unsigned short)CODE_SEL;
  TABLE[vector].ZEROS      = 0;
  TABLE[vector].FLAGS      = 0x8E;
  TABLE[vector].BASE_HIGH  = (unsigned short)((ptr >> 16) & 0xFFFF);
}

