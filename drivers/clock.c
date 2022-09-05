#include "clock.h"
void (*game_loop)(void) = 0;

static void timer_callback(void)
{
        if (game_loop != 0)
                game_loop();

        eoi_master();
}

void init_clock(uint32_t freq)
{
        init_timer(timer_callback);

        uint32_t divisor = 1193180 / freq;
        uint8_t low  = (uint8_t)(divisor & 0xFF);
        uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);

        outb(0x43, 0x36);
        outb(0x40, (uint8_t)low);
        outb(0x40, (uint8_t)high);
}

void register_callback(void* callback) {
        game_loop = callback;
}
