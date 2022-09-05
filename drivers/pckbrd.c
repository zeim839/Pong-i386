#include "pckbrd.h"

int read_scancode (uint8_t code, unsigned char* out)
{
        // Only handle the keys necessary for the game
        switch (code) {
        case 0x11:
                *out = 'w';
                break;
        case 0x18:
                *out = 'o';
                break;
        case 0x1F:
                *out = 's';
                break;
        case 0x25:
                *out = 'k';
                break;
        case 0x39: // SPACE, pass as z
                *out = 'z';
                break;
        default:
                return FALSE;
        }

        return TRUE;
}

void kb_handler(void)
{
        unsigned char out;
        uint8_t code = inb(KEYBD);
        int i = read_scancode(code, &out);

        if (i) {
                // Move game paddles
                switch(out) {
                case 'w':         // Player A up
                        mov_boardA(1);
                        break;
                case 's':         // Player A down
                        mov_boardA(-1);
                        break;
                case 'o':         // Player B up
                        mov_boardB(1);
                        break;
                case 'k':         // Player B down
                        mov_boardB(-1);
                        break;
                case 'z':
                        reset_assets();
                        reset_score();
                        unlock_drawing();
                        break;
                }
        }

        eoi_master();
}

void kb_init()
{
        // Clear unread buffer
        inb(KEYBD);

        // Register interrupt handler
        init_keyboard(kb_handler);
}
