#include "textmode.h"

/* Keep track of current position in terminal */
size_t ROW = 0;
size_t COLUMN = 0;

uint8_t vga_entry_color (enum VGA_COLOR fg, enum VGA_COLOR bg) {
  return fg | bg << 4;
}

uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t) uc | (uint16_t) color << 8;
}

void vga_clear()
{
  uint16_t color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK);
  uint16_t entry = vga_entry(' ', color);
  uint16_t* buffer = BUFFER_BASE;
  for (size_t i = 0; i < (VGA_HEIGHT * VGA_WIDTH); i++) {
    *buffer = entry;
    buffer++;
  }
  ROW = COLUMN = 0;
}

void print_char (unsigned char uc, uint8_t clr)
{
  uint16_t* buffer = BUFFER_BASE;
  if (COLUMN >= VGA_WIDTH) {
    COLUMN = 0;
    ROW++;
  }

  if (ROW >= VGA_HEIGHT)
    scroll_up(1);

  buffer[(VGA_WIDTH * ROW) + COLUMN]
    = vga_entry(uc, clr);

  COLUMN++;
}

void print (unsigned char* ptr)
{
  /* All strings end with an EOF character. Print until
  it is found.*/
  while (*ptr != EOF) {
    print_char(*ptr, 15);
    ptr++;
  }
}


void println (unsigned char* ptr)
{
  /* No point incrementing ROW unless we're not already
  on a new line.*/
  if (COLUMN != 0) {
    ROW++;
    COLUMN = 0;
  }

  print(ptr);
}

void scroll_up (size_t rows)
{
  if (rows > ROW)
    rows = ROW;

  size_t end = VGA_WIDTH * rows;
  uint16_t* buffer = BUFFER_BASE;

  /* Shift everything up by the specified number of
  rows, overwriting existing data.*/
  for (size_t i = end; i < (VGA_HEIGHT * VGA_WIDTH); i++) {
    *buffer = buffer[end];
    buffer++;
  }

  size_t start = (VGA_HEIGHT * VGA_WIDTH) - rows*VGA_WIDTH;
  uint16_t blank_entry = vga_entry(' ', VGA_COLOR_BLACK);
  buffer = BUFFER_BASE;

  /* Everything has been shifted upwards. Fill the bottom
  rows with empty black space.*/
  for (size_t i = start; i < (VGA_HEIGHT * VGA_WIDTH); i++)
    buffer[i] = blank_entry;

  ROW -= rows;
}
