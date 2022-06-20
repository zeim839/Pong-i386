#include "pckbrd.h"

int kb_has_input = FALSE;
unsigned char in_buffer;

int read_scancode (uint8_t code, unsigned char* out)
{
  /* Only handle the keys necessary for the game */
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

int kb_getchar(unsigned char* out)
{
  if (!kb_has_input) return FALSE;
  *out = in_buffer;
  kb_has_input = FALSE;
  return TRUE;
}

void kb_handler(void)
{
  unsigned char out;
  uint8_t code = inb(KEYBD);
  int i = read_scancode(code, &out);

  if (i) {
    kb_has_input = TRUE;
    in_buffer = out;
  }

  eoi_master();
}

void kb_init()
{
  /* Clear unread buffer */
  inb(KEYBD);

  /* Register interrupt handler */
  init_keyboard(kb_handler);
}
