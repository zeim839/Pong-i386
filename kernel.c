#include "arch/interrupts.h"
#include "drivers/clock.h"
#include "drivers/pckbrd.h"
#include "graphics/assets.h"

extern void load_gdt();
uint32_t freq = 40;
int direction = 0;

void game(void)
{
  int _dir = handle_ball();
  if (_dir != direction && _dir == 1)
    init_clock(freq/1.5);

  if (_dir != direction && _dir == 0)
    init_clock(freq);

  direction = _dir;
  draw_assets();
}

void sys_init(void)
{
  load_gdt();
  init_interrupts();

  init_clock(freq);
  kb_init();

  reset_assets();
  register_callback(game);
  title_screen();
}

void kernel_entry()
{
  sys_init();
  for(;;) asm("hlt");
}
