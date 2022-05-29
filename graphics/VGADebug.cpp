#include "VGADebug.h"

size_t VGADebug::row = 0;
size_t VGADebug::column = 0;

/* First 4 bits are bg, last 4 bits are fg */
uint8_t VGADebug::VGAEntryColor (
    enum VGA_COLOR fg, 
    enum VGA_COLOR bg
) { return fg | bg << 4; }

/* First byte is color, last byte is uc */
uint16_t VGADebug::vgaEntry (
    unsigned char uc, 
    uint8_t color
) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t VGADebug::bufferIndex (
    size_t row, 
    size_t column
) {
    row = (row % VGA_ROWS);

    if (column >= VGA_COLUMNS) {
        row++;
        column = (column % VGA_COLUMNS);
    }

    return (row * VGA_COLUMNS) + column;
}

void VGADebug::Clear () {
    for (size_t y = 0; y < VGA_ROWS; y++) {
        for (size_t x = 0; x < VGA_COLUMNS; x++ ) {
            size_t i = bufferIndex(y, x);
            uint16_t entry = vgaEntry(' ', EMPTY_ENTRY);
            buffer[i] = entry;
        }
    }
    row = 0;
    column = 0;
}

void VGADebug::Print ( 
    unsigned char* ptr, 
    size_t len,
    uint8_t clr
) {
    size_t newIndex = (row*VGA_COLUMNS) + column + len;
    size_t maxIndex = bufferIndex(VGA_ROWS - 1, VGA_COLUMNS - 1);
    if (newIndex > maxIndex) {
        size_t n = ((newIndex - maxIndex)/(VGA_COLUMNS - 1)) + 1;
        ScrollUp(n);
    }

    if (column + len >= VGA_COLUMNS) {
        len = VGA_COLUMNS - column - 1;
    }

    for (size_t i = 0; i<len; i++) {
        uint16_t entry = vgaEntry(ptr[i], clr);
        size_t pos = bufferIndex(row, column + 1);
        buffer[pos] = entry;
        column++;
    }
}

void VGADebug::Println (
    unsigned char* ptr, 
    size_t len,
    uint8_t clr
) {
    if (!(row == 0 && column == 0)) {
        row++;
    }
    column = 0;
    Print(ptr, len, clr);
}

void VGADebug::shiftclr (size_t n) {
    for (size_t y = 0; y< VGA_ROWS; y++) {
        for (size_t x = 0; x < VGA_COLUMNS; x++) {
            size_t i = bufferIndex(y, x);
            size_t m = i + n;
            if (m >= 2000) return;
            buffer[i] = buffer[m];
            buffer[m] = EMPTY_ENTRY;
        }
    }
}

void VGADebug::ScrollUp (size_t n) {
    size_t _n = bufferIndex(n, 0);
    shiftclr(_n);
    if (n > row) {
        row = 0;
        return;
    }
    row -= n;
}