#ifndef INT_HANDLE_H
#define INT_HANDLE_H

extern void itge_reserved ();
extern void irq_unsupported_mstr();
extern void irq_unsupported_slve();

extern void itge_divide_zero ();
extern void itge_debug ();
extern void itge_non_mask_int ();
extern void itge_breakpoint ();
extern void itge_overflow ();
extern void itge_bound_exceed ();
extern void itge_invalid_op ();
extern void itge_device_na ();
extern void itge_double_fault ();
extern void itge_coproc_seg_overr ();
extern void itge_invalid_tss ();
extern void itge_segment_na ();
extern void itge_ss_fault ();
extern void itge_gp_fault ();
extern void itge_pg_fault ();
extern void itge_float_pt ();
extern void itge_align_chk ();
extern void itge_mach_chk ();
extern void itge_SIMD_float_pt ();
extern void itge_virt_exc ();
extern void itge_ctrlp_exc ();

extern void irq_timer();
extern void irq_keyboard();

#endif
