#include "ports.h"

uint8_t inb (uint8_t port)
{
  uint8_t portb;
  asm volatile("inb %%dx, %%al" : "=a"(portb) : "d"(port));
  return portb;
}

void outb(uint8_t port, uint16_t data)
{
  asm volatile("outb %%al, %%dx" : : "a"(data), "d"(port));
}
