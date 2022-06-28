#ifndef ASSETS_H
#define ASSETS_H

#include "../drivers/textmode.h"
#include "windows.h"

#define PRIMARY_INIT_TOP  10
#define SECOND_INIT_TOP   10
#define PRIMARY_COL       1
#define SECONDARY_COL     78

#define BALL_INIT_X       40
#define BALL_INIT_Y       11

/* Draw the assets on the VGA window. Must be in game
window or elements will overlap.*/
void draw_assets();

/* Enable/disable drawing game assets. Useful when displaying
a title screen or window.*/
void lock_drawing();
void unlock_drawing();

/* Reset asset score/positions to default values */
void reset_assets();
void reset_score();

/* Converts num to an unsigned char */
unsigned char num2char(size_t num);

/* Move the player paddles vertically by y steps. Negative
integers go down, positives go up.*/
void mov_boardA(int y);
void mov_boardB(int y);

/* Move the ball horizontally by x steps. Positive integers
for right, negative for left. */
void mov_ball_horiz(int x);

/* Move the ball diagonally by y steps. If dir is 0, the
ball will move left->right. If dir is 1, the ball moves
right->left. Positive y numbers go up, negative y numbers
go down.*/
void mov_ball_diag(size_t dir, int y);

/* Checks if the ball has collided with a paddle, wall
or border. Consequently handles bouncing, score keeping. */
int handle_ball();

/* Increments the score for player a or player b. Set a
parameter to 0 if no increment.*/
void increment_score(size_t a, size_t b);

#endif
