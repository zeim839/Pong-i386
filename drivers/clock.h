#ifndef CLOCK_H
#define CLOCH_H

#include <stddef.h>
#include <stdint.h>

#include "textmode.h"
#include "../arch/interrupts.h"

void init_clock(uint32_t freq);
void register_callback(void* callback);

#endif
