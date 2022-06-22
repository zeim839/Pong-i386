#include "assets.h"

/*=============================
          ASSET STATE
  =============================  */
size_t PRIMARY_POS_Y, SECOND_POS_Y,  BALL_X,  
  BALL_Y, BALL_DIR;

size_t SCORE_A = 0;
size_t SCORE_B = 0;

void reset_assets()
{
  PRIMARY_POS_Y  = PRIMARY_INIT_TOP;
  SECOND_POS_Y   = SECOND_INIT_TOP;
  BALL_X         = BALL_INIT_X;
  BALL_Y         = BALL_INIT_Y;
  BALL_DIR       = 1;

  draw_assets();
}

void draw_assets()
{
  vga_clear();
  uint8_t clr = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_WHITE);

  /* Board A */
  put_char(' ', PRIMARY_POS_Y, PRIMARY_COL, clr);
  put_char(' ', PRIMARY_POS_Y + 1, PRIMARY_COL, clr);
  put_char(' ', PRIMARY_POS_Y + 2, PRIMARY_COL, clr);

  /* Board B */
  put_char(' ', SECOND_POS_Y, SECONDARY_COL, clr);
  put_char(' ', SECOND_POS_Y + 1, SECONDARY_COL, clr);
  put_char(' ', SECOND_POS_Y + 2, SECONDARY_COL, clr);

  /* Ball */
  put_char(' ', BALL_Y, BALL_X, clr);

  /* Score board */
  unsigned char scr[] = "Score: ";
  print_at(&scr[0], 24, 0);
}

/*=============================
        ASSET POSITION
  =============================  */

void move_asset(int x, int max, size_t* asset_pos)
{
  int pos = (int) *asset_pos;
  pos += x;

  if (pos < 0)
    pos = 0;
  if (pos >= max - 1)
    pos = max - 1;

  *asset_pos = (size_t) pos;
}

void mov_boardA(int y) {
  move_asset(-y, 23, &PRIMARY_POS_Y);
}

void mov_boardB(int y) {
  move_asset(-y, 23, &SECOND_POS_Y);
}

void mov_ball_horiz(int x) {
  move_asset(x, 80, &BALL_X);
}

void mov_ball_diag(size_t dir, int y)
{
  int x = (dir == 0) ? y : -y;
  move_asset(x, 80, &BALL_X);
  move_asset(-y, 24, &BALL_Y);
}

void move_ball() 
{
  switch (BALL_DIR) {
  case 0: /* Move right */
    mov_ball_horiz(1);
    break;
  case 1: /* Move left */
    mov_ball_horiz(-1);
    break;
  case 2: /* Up and to the right */
    mov_ball_diag(0, 1);
    break;
  case 3: /* Down and to the right */
    mov_ball_diag(1, -1);
    break;
  case 4: /* Up and to the left */
    mov_ball_diag(1, 1);
    break;
  case 5: /* Down and to the left */
    mov_ball_diag(0, -1);
    break;
  }
}

void handle_collision()
{
  if (BALL_X == 2 && BALL_Y == PRIMARY_POS_Y + 1) {
    BALL_DIR = 0;
    return;
  }

  if (BALL_X == 2 && BALL_Y == PRIMARY_POS_Y + 2) {
    BALL_DIR = 3;
    return;
  }

  if (BALL_X == 2 && BALL_Y == PRIMARY_POS_Y) {
    BALL_DIR = 2;
    return;
  }

  if (BALL_X == 77 && BALL_Y == SECOND_POS_Y + 1) {
    BALL_DIR = 1;
    return;
  }

  if (BALL_X == 77 && BALL_Y == SECOND_POS_Y + 2) {
    BALL_DIR = 5;
    return;
  }

  if (BALL_X == 77 && BALL_Y == SECOND_POS_Y) {
    BALL_DIR = 4;
    return;
  }

  if (BALL_Y == 0 && BALL_DIR == 2) {
    BALL_DIR = 3;
    return;
  }

  if (BALL_Y == 0 && BALL_DIR == 4) {
    BALL_DIR = 5;
    return;
  }

  if (BALL_Y == 23 && BALL_DIR == 3) {
    BALL_DIR = 2;
    return;
  }

  if (BALL_Y == 23 && BALL_DIR == 5) {
    BALL_DIR = 4;
    return;
  }
}

void handle_ball()
{
  if (BALL_X == 0) {
    increment_score(0, 1);
    reset_assets();
    return;
  }

  if (BALL_X == 79) {
    increment_score(1, 0);
    reset_assets();
    return;
  }

  move_ball();
  handle_collision();
}

void increment_score(size_t a, size_t b)
{
  SCORE_A += a;
  SCORE_B += b;
}

