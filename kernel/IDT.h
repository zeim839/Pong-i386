#ifndef IDT_H
#define IDT_H

#include <stddef.h>
#include <stdint.h>
#include "ISR.h"
#include "../graphics/VGADebug.h"

namespace IDT {
  
typedef struct {
    unsigned short  BASE_LOW;                       // Low word of entry address into ISR
    unsigned short  SEL;                            // Segment selector
    unsigned char   ZEROS;                          // Not used/always zero 
    unsigned char   FLAGS;                          // MSB (5 bits), DPL (2 bits), P (1 bit)
    unsigned short  BASE_HIGH;                      // High word of entry address into ISR
} __attribute__((packed)) 
GATE;

typedef struct {
    unsigned short  LIMIT;                          // IDT Size - 1
    unsigned int    BASE;                           // Entry address of IDT
}__attribute__((packed)) 
DESC;                                    

#define TABLE_SIZE (sizeof(GATE) * 256)

/* Passes the IDT descriptor table to CPU. */
extern "C" void _lidt (unsigned int ptr);

extern "C" unsigned char CODE_SEL;

/* Sets IDT entry no. 'id' to fnPtr with the specified flags.*/
void setGate (
    size_t id,
    unsigned char flags,
    unsigned int fnPtr
);

void clearTable ();

/* Sets ISRDefaultHandler as the ISR exception handler. 
Any exception interrupts (0-18) get halted and printed to 
the screen.*/
void initDefaultISR ();

/* Initializes reserved intel default ISR's (0-31), then loads 
IDT to CPU. Should probably run clearTable() before the first time
setIDT() is ran. */
void setIDT ();  
}

#endif
