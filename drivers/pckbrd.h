#ifndef PCKBRD_H
#define PCKBRD_H

#include "../arch/include/ports.h"
#include "../arch/interrupts.h"

#define KEYBD  0x60
#define TRUE   1
#define FALSE  0

int kb_getchar(unsigned char* out);
void kb_handler(void);
void kb_init();

#endif
