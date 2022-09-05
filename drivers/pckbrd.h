#ifndef PCKBRD_H
#define PCKBRD_H

#include "../arch/ports.h"
#include "../arch/interrupts.h"
#include "../graphics/assets.h"

#define KEYBD  0x60
#define TRUE   1
#define FALSE  0

void kb_handler(void);
void kb_init();

#endif
