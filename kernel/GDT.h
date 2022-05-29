/* src: GDT.s */
#ifndef GDT_H
#define GDT_H

namespace GDT {

typedef struct {
    unsigned short  LIMIT_LO;           // Low word of segment limit.
    unsigned short  BASE_LO;            // Low word of segment base.
    unsigned char   BASE_MD;            // Middle bit of segment base.
    unsigned char   ACCESS;             // Access flag (bit).
    unsigned char   GRAN;               // Granularity (bit).
    unsigned char   BASE_HI;            // High word of segment base.
} __attribute__((packed)) 
GDT_ENTRY;

/* GDTP entry, should be 48 bits.*/
typedef struct {
    unsigned short  LIMIT;              // Word: Size of GDT in bits minus 1
    unsigned long   BASE;               // Word: Base of GDT == &GDT[0]
} __attribute__((packed))
GDTP;

/* Loads the GDT_DESC into the CPU and then reloads
the segment registers for the new GDT to take effect*/
extern "C" void loadGDTP();

/* GDT entries. */
extern "C" GDT_ENTRY GDT_CODE;
extern "C" GDT_ENTRY GDT_DATA;
extern "C" GDT_ENTRY GDT_NULL_DESCRIPTOR;

/* GDT descriptor. Loaded into the CPU when loadGDTP is 
called.*/
extern "C" GDTP GDT_DESC;

}

#endif