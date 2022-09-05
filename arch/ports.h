#ifndef PORTS_H
#define PORTS_H

#include <stddef.h>
#include <stdint.h>

uint8_t inb(uint8_t port);
void outb(uint8_t port, uint16_t data);

#endif
