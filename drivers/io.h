#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <stdint.h>

/* Reads a byte from the specified I/O port*/
uint8_t inb (uint16_t port);

/* Writes the byte 'val' to the specified 'port'*/
void outb (uint16_t port, uint8_t val);

/* Creates a delay of a few microseconds.*/
void wait (void);

#endif
