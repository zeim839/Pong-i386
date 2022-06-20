#ifndef TEXTMODE_H
#define TEXTMODE_H

#include <stddef.h>
#include <stdint.h>
#include "../arch/include/ports.h"

#define BUFFER_BASE (uint16_t*)0xB8000
#define VGA_HEIGHT  25
#define VGA_WIDTH   80
#define EOF         '\0'

/* VGA text mode color constants. */
enum VGA_COLOR {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15
};

/* Clear the buffer by setting everything to black. */
void vga_clear();

/* Creates a VGA text mode entry with text 'uc' and
color 'color'*/
uint16_t vga_entry(unsigned char uc, uint8_t color);

/* Computes a VGAEntry color given a foreground 'fg' and
background 'bg' */
uint8_t vga_entry_color (enum VGA_COLOR fg, enum VGA_COLOR bg);

/* Removes 'n' rows from the top of the terminal, and
moves all subsequent rows 'n' units up. */
void scroll_up (size_t rows);

/* Prints a character at the next available buffer index */
void print_char (unsigned char uc, uint8_t clr);

/* Prints a string */
void print(unsigned char* ptr);

/* Prints a string starting at the next available row. */
void println(unsigned char* ptr);

#endif
