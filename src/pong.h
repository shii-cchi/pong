#ifndef SRC_PONG_H_
#define SRC_PONG_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FIELD_X 80
#define MAX_FIELD_Y 25
#define MIN_FIELD 0
#define FIELD_X_MIDDLE 41
#define FIELD_Y_MIDDLE 13
#define START_SCORE 0
#define MAX_SCORE 21
#define LEFT_DOWN 1
#define LEFT_UP 2
#define RIGHT_UP 3
#define RIGHT_DOWN 4

void print_rules();
void clear_screen();
void win(int score_1);
void move_racket(int *racket_1, int *racket_2, char button);
int move_field(int racket_1, int racket_2, int ball_x, int ball_y, int score_1,
               int score_2);
int how_move_ball(int ball_x, int ball_y, int ball_orientation, int racket_1,
                  int racket_2);
int just_move(int ball_orientation);
int bounce(int ball_x, int ball_y, int ball_orientation);
int score_ball(int ball_x, int ball_y, int ball_orientation, int racket_1,
               int racket_2);
int hit_ball(int ball_x, int ball_y, int ball_orientation, int racket_1,
             int racket_2);
void move_ball(int *ball_x, int *ball_y, int ball_position,
               int *ball_orientation, int *score_1, int *score_2);

#endif  // SRC_PONG_H_
