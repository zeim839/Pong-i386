#include "arch/interrupts.h"
#include "drivers/textmode.h"
#include "drivers/clock.h"
#include "drivers/pckbrd.h"
extern void load_gdt();

/* Temp. keyboard driver test. Will be replaced
with main game loop in the future.*/
void game(void)
{
  unsigned char out = ' ';
  int i = kb_getchar(&out);

  if (i) print(&out);
}

void sys_init(void)
{
  load_gdt();
  init_interrupts();

  init_clock(50);
  kb_init();

  register_callback(game);
}

void kernel_entry()
{
  sys_init();

  /* @TODO: Pong Game*/

  for(;;) asm("hlt");
}

