#ifndef VGADEBUG_H
#define VGADEBUG_H

#include <stddef.h>
#include <stdint.h>

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

/* Implements a simple debugging terminal 
via the BIOS VGA text mode. */
class VGADebug {
private:
    const uint16_t* BUFFER_BASE = (uint16_t*) 0xB8000;
    const size_t VGA_COLUMNS = 80;
    const size_t VGA_ROWS = 25;
    const uint16_t EMPTY_ENTRY = 1;

    /* Shift and clear: moves every entry in the VGA buffer 'n' elements
    to the right/left, starting with element 'base', and fills any vacant
    entries with a VGA_COLOR_BLACK entry. */
    void shiftclr (size_t n);

    /* Given a row and a column, bufferIndex computes the 
    respective VGA buffer index. */
    size_t bufferIndex (
        size_t row, 
        size_t column
    );
    
    /* Creates a VGA text mode entry with text 'uc' and 
    color 'color'*/
    uint16_t vgaEntry (
        unsigned char uc, 
        uint8_t color
    );

    /* Tracks the next row/column, static to prevent 
    overwriting existing entries */
    static size_t row, column;

    /* Non-const pointer to buffer base, used in modifying
    the buffer */
    uint16_t* buffer = (uint16_t*) BUFFER_BASE;

public:

    /* Removes 'n' rows from the top of the terminal, and
    moves all subsequent rows 'n' units up. */
    void ScrollUp (size_t n);

    /* Computes a VGAEntry color given a foreground 'fg' and
    background 'bg' */
    uint8_t VGAEntryColor (
        enum VGA_COLOR fg, 
        enum VGA_COLOR bg
    );

    /* Prints a char array starting at the next available column. 
    Ignores chars that dont fit into the current row. */
    void Print ( 
        unsigned char* ptr, 
        size_t len,
        uint8_t clr = 15
    );

    /* Prints a char array starting at the next available row. */
    void Println (
        unsigned char* ptr, 
        size_t len,
        uint8_t clr = 15
    );

    /* Clears the terminal screen */
    void Clear ();
};

#endif