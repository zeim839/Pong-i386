#include "windows.h"

void title_screen()
{
        vga_clear();

        unsigned char title[]  = "Pong-i386";
        unsigned char ctrls[]  = "Controls:";
        unsigned char pa[]     = "Player A: W/S   |   Player B: O/K";
        unsigned char instr[]  = "Press [space] to start";

        print_at(&title[0], 10, 35);
        print_at(&instr[0], 13, 29);
        print_at(&ctrls[0], 22, 35);
        print_at(&pa[0], 23, 23);
}

void player_a_wins()
{
        vga_clear();

        unsigned char title[] = "Player A Wins!";
        unsigned char instr[] = "Press [space] to restart";

        print_at(&title[0], 10, 33);
        print_at(&instr[0], 13, 28);
}

void player_b_wins()
{
        vga_clear();

        unsigned char title[] = "Player B Wins!";
        unsigned char instr[] = "Press [space] to restart";

        print_at(&title[0], 10, 33);
        print_at(&instr[0], 13, 28);
}
