#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stddef.h>
#include <stdint.h>
#include "archconst.h"
#include "isr.h"
#include "../drivers/textmode.h"
#include "ports.h"

// In gdt.s
extern uint16_t CODE_SEL;
extern uint16_t DATA_SEL;

// IDT Entry
struct irq_hook {
        unsigned short  BASE_LOW;
        unsigned short  SEL;
        unsigned char   ZEROS;
        unsigned char   FLAGS;
        unsigned short  BASE_HIGH;
} __attribute__((packed));

// IDT pointer. This is input struct for the lidt opcode
struct irq_table {
        unsigned short  LIMIT;
        uint32_t           BASE;
} __attribute__((packed));

/*
 * registers_t represents the state of the stack when int_handle
 * is called. See ./include/isr.s
 */
struct registers_t {
        uint32_t DS;
        uint32_t EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
        uint32_t INTR;
        uint32_t EIP, CS, EFLAGS, USERESP, SS;
} __attribute((packed));

#define TABLE_SIZE (sizeof(struct irq_hook) * 256)

/*
 * Remaps PIC interrupt vectors, since they're otherwise
 * mapped to reserved CPU interrups.
 */
void remap_pic();

// Mask/unmask a particular interrupt.
void mask_irq(uint8_t irq);
void unmask_irq(uint8_t irq);

/*
 * Acknowledge an interrupt and send the end-of-interrupt
 * (eoi) message.
 */
void eoi_master();
void eoi_slave();

/*
 * Given an interrupt vector 'intr', this function decides
 * which service routine or hardware IRQ handler to call.
 */
void int_handle(struct registers_t registers);

/*
 * Register an irq_hook with address 'base' at the specified
 * 'vector' index of the interrupt descriptor table.
 */
void register_hook(size_t vector, uint32_t base);

/*
 * Register handlers/drivers for IRQs, where 'base' is the
 * address of the handler function.
 */
void init_timer(void* base);
void init_keyboard(void* base);

void load_IDT();
void clear_table();

/*
 * Configure all interrupt routines. All that's left to do
 * is to initialize timer & keyboard handlers.
 */
void init_interrupts();

#endif
