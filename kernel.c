#include "arch/interrupts.h"
#include "drivers/textmode.h"
#include "drivers/clock.h"
#include "drivers/pckbrd.h"
#include "graphics/assets.h"

extern void load_gdt();

void game(void)
{
  handle_ball();
  draw_assets();

  unsigned char out = ' ';
  int i = kb_getchar(&out);
  if (i) {
    switch(out) {
    case 'w':
      mov_boardA(1);
      break;
    case 's':
      mov_boardA(-1);
      break;
    case 'o':
      mov_boardB(1);
      break;
    case 'k':
      mov_boardB(-1);
      break;
    }
  }
}

void sys_init(void)
{
  load_gdt();
  init_interrupts();

  init_clock(30);
  kb_init();

  reset_assets();
  register_callback(game);
}

void kernel_entry()
{
  sys_init();
  /* @TODO: Pong Game*/

  for(;;) asm("hlt");
}
