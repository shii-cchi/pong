#include "pong.h"

int main() {
  int racket_1 = FIELD_Y_MIDDLE, racket_2 = FIELD_Y_MIDDLE;
  int ball_x = FIELD_X_MIDDLE, ball_y = FIELD_Y_MIDDLE;
  int ball_orientation = LEFT_DOWN;
  int score_1 = START_SCORE, score_2 = START_SCORE;
  int ball_position = 0;
  char key = 0;
  print_rules();
  if (scanf("%c", &key)) {
    key = getchar();
    move_field(racket_1, racket_2, ball_x, ball_y, score_1, score_2);
    while (score_1 != MAX_SCORE && score_2 != MAX_SCORE) {
      key = getchar();
      move_racket(&racket_1, &racket_2, key);
      clear_screen();
      ball_position =
          how_move_ball(ball_x, ball_y, ball_orientation, racket_1, racket_2);
      move_ball(&ball_x, &ball_y, ball_position, &ball_orientation, &score_1,
                &score_2);
      move_field(racket_1, racket_2, ball_x, ball_y, score_1, score_2);
      if (score_1 == MAX_SCORE || score_2 == MAX_SCORE) {
        win(score_1);
      }
    }
  }
  return 0;
}

void print_rules() {
  printf(
      "\t\t\t\t\tPONG\n\n\t\t1) to move the left racket press 'z'(down) or "
      "'a'(up)\n\t\t2) to move the right racket press 'm'(down) or "
      "'k'(up)\n\t\t3) the player, who scores 21 points, will "
      "win\n\n\t\t\tpress any key and 'enter' to start the game\n");
}

void clear_screen(void) { printf("\33[0d\33[2J"); }

void win(int score_1) {
  clear_screen();
  if (score_1 == MAX_SCORE) {
    printf("PLAYER 1 WINS\n");
  } else {
    printf("PLAYER 2 WINS\n");
  }
}

void move_racket(int *racket_1, int *racket_2, char button) {
  switch (button) {
    case 'a':
      if ((*racket_1 + 2) != MAX_FIELD_Y + 1) {
        *racket_1 += 1;
      }
      break;
    case 'z':
      if ((*racket_1 - 2) != MIN_FIELD) {
        *racket_1 -= 1;
      }
      break;
    case 'k':
      if ((*racket_2 + 2) != MAX_FIELD_Y + 1) {
        *racket_2 += 1;
      }
      break;
    case 'm':
      if ((*racket_2 - 2) != MIN_FIELD) {
        *racket_2 -= 1;
      }
      break;
    default:
      break;
  }
}

int move_field(int racket_1, int racket_2, int ball_x, int ball_y, int score_1,
               int score_2) {
  int field_length = MAX_FIELD_X + 1, field_width = MAX_FIELD_Y + 1;
  do {
    for (int i = 0; i <= field_length; i++) {
      if ((field_width == MIN_FIELD) || (field_width == MAX_FIELD_Y + 1)) {
        printf("-");
      } else {
        if (field_width == MAX_FIELD_Y && i == FIELD_X_MIDDLE - 2 &&
            score_1 <= 9) {
          printf("% d||", score_1);
          i = i + 3;
        }
        if ((field_width == MAX_FIELD_Y) && (i == FIELD_X_MIDDLE - 2) &&
            (score_1 > 9)) {
          printf("%d||", score_1);
          i = i + 3;
        }
        if ((field_width == MAX_FIELD_Y) && (i == FIELD_X_MIDDLE + 1) &&
            (score_2 <= 9)) {
          printf("%d  ", score_2);
          i = i + 3;
        }
        if ((field_width == MAX_FIELD_Y) && (i == FIELD_X_MIDDLE + 1) &&
            (score_2 > 9)) {
          printf("%d ", score_2);
          i = i + 3;
        } else {
          if (((i == MIN_FIELD) || (i == MAX_FIELD_X)) &&
              (field_width != MIN_FIELD) && (field_width != MAX_FIELD_Y + 1)) {
            printf("|");
            i += 1;
          }
          if ((i == ball_x) && (field_width == ball_y)) {
            printf("o");
            if ((i != FIELD_X_MIDDLE) || (field_width != FIELD_Y_MIDDLE)) {
              i += 1;
            }
            if ((i == FIELD_X_MIDDLE + 1) && (field_width != FIELD_Y_MIDDLE)) {
              i -= 1;
            }
          }
          if ((i == FIELD_X_MIDDLE) && (field_width != MIN_FIELD) &&
              (field_width != MAX_FIELD_Y + 1) &&
              ((field_width != ball_y) || (i != ball_x))) {
            printf("||");
            i += 1;
          }
          if ((i == MIN_FIELD + 1) &&
              ((field_width == racket_1) || (field_width == racket_1 + 1) ||
               (field_width == racket_1 - 1))) {
            printf("]");
            i += 1;
          }
          if ((i == MAX_FIELD_X - 1) &&
              ((field_width == racket_2) || (field_width == racket_2 + 1) ||
               (field_width == racket_2 - 1))) {
            printf("[|");
            i += 1;
          }
        }
        printf(" ");
      }
    }
    field_width -= 1;
    printf("\n");
  } while (field_width >= 0);
  return 0;
}

int how_move_ball(int ball_x, int ball_y, int ball_orientation, int racket_1,
                  int racket_2) {
  int ball_position = 0;
  if ((ball_x != MAX_FIELD_X - 2) && (ball_x != MIN_FIELD + 2) &&
      (ball_y != MAX_FIELD_Y) && (ball_y != MIN_FIELD + 1)) {
    ball_position = just_move(ball_orientation);
  } else {
    ball_position = bounce(ball_x, ball_y, ball_orientation);
    if (!ball_position) {
      ball_position =
          score_ball(ball_x, ball_y, ball_orientation, racket_1, racket_2);
    }
    if (!ball_position) {
      ball_position =
          hit_ball(ball_x, ball_y, ball_orientation, racket_1, racket_2);
    }
  }
  return ball_position;
}

int just_move(int ball_orientation) {
  int ball_position = 0;
  switch (ball_orientation) {
    case 1:
      ball_position = 1;
      break;
    case 2:
      ball_position = 2;
      break;
    case 3:
      ball_position = 3;
      break;
    case 4:
      ball_position = 4;
      break;
  }
  return ball_position;
}

int bounce(int ball_x, int ball_y, int ball_orientation) {
  int ball_position = 0;
  if ((ball_y == MIN_FIELD + 1) && (ball_x != MIN_FIELD + 2) &&
      (ball_orientation == LEFT_DOWN)) {
    ball_position = 5;
  }
  if ((ball_y == MIN_FIELD + 1) && (ball_x != MAX_FIELD_X - 2) &&
      (ball_orientation == RIGHT_DOWN)) {
    ball_position = 6;
  }
  if ((ball_y == MAX_FIELD_Y) && (ball_x != MIN_FIELD + 2) &&
      (ball_orientation == LEFT_UP)) {
    ball_position = 7;
  }
  if ((ball_y == MAX_FIELD_Y) && (ball_x != MAX_FIELD_X - 2) &&
      (ball_orientation == RIGHT_UP)) {
    ball_position = 8;
  }
  return ball_position;
}

int score_ball(int ball_x, int ball_y, int ball_orientation, int racket_1,
               int racket_2) {
  int ball_position = 0;
  if ((ball_x == MIN_FIELD + 2) &&
      ((ball_y != racket_1) && (ball_y != racket_1 - 1) &&
       (ball_y != racket_1 + 1))) {
    if ((ball_orientation == LEFT_DOWN) || ball_orientation == LEFT_UP) {
      ball_position = 9;
    } else {
      if (ball_orientation == RIGHT_DOWN) {
        ball_position = 4;
      } else {
        ball_position = 3;
      }
    }
  }
  if ((ball_x == MAX_FIELD_X - 2) &&
      ((ball_y != racket_2) && (ball_y != racket_2 - 1) &&
       (ball_y != racket_2 + 1))) {
    if ((ball_orientation == RIGHT_UP) || ball_orientation == RIGHT_DOWN) {
      ball_position = 10;
    } else {
      if (ball_orientation == LEFT_UP) {
        ball_position = 2;
      } else {
        ball_position = 1;
      }
    }
  }
  return ball_position;
}

int hit_ball(int ball_x, int ball_y, int ball_orientation, int racket_1,
             int racket_2) {
  int ball_position = 0;
  if ((ball_x == MIN_FIELD + 2) &&
      ((ball_y == racket_1) || (ball_y == racket_1 - 1) ||
       (ball_y == racket_1 + 1))) {
    if (ball_orientation == LEFT_UP) {
      ball_position = 11;
    } else {
      ball_position = 12;
    }
  }
  if ((ball_x == MAX_FIELD_X - 2) &&
      ((ball_y == racket_2) || (ball_y == racket_2 - 1) ||
       (ball_y == racket_2 + 1))) {
    if (ball_orientation == RIGHT_UP) {
      ball_position = 13;
    } else {
      ball_position = 14;
    }
  }
  return ball_position;
}

void move_ball(int *ball_x, int *ball_y, int ball_position,
               int *ball_orientation, int *score_1, int *score_2) {
  srand(time(NULL));
  switch (ball_position) {
    case 1:
      *ball_x -= 1;
      *ball_y -= 1;
      break;
    case 2:
      *ball_x -= 1;
      *ball_y += 1;
      break;
    case 3:
      *ball_x += 1;
      *ball_y += 1;
      break;
    case 4:
      *ball_x += 1;
      *ball_y -= 1;
      break;

    case 5:
      *ball_x -= 1;
      *ball_y += 1;
      *ball_orientation = LEFT_UP;
      break;
    case 6:
      *ball_x += 1;
      *ball_y += 1;
      *ball_orientation = RIGHT_UP;
      break;
    case 7:
      *ball_x -= 1;
      *ball_y -= 1;
      *ball_orientation = LEFT_DOWN;
      break;
    case 8:
      *ball_x += 1;
      *ball_y -= 1;
      *ball_orientation = RIGHT_DOWN;
      break;

    case 9:
      *ball_x = 41;
      *ball_y = 13;
      *ball_orientation = rand() % 4 + 1;
      *score_2 += 1;
      break;
    case 10:
      *ball_x = 41;
      *ball_y = 13;
      *ball_orientation = rand() % 4 + 1;
      *score_1 += 1;
      break;

    case 11:
      *ball_x += 1;
      *ball_y += 1;
      *ball_orientation = RIGHT_UP;
      break;
    case 12:
      *ball_x += 1;
      *ball_y -= 1;
      *ball_orientation = RIGHT_DOWN;
      break;
    case 13:
      *ball_x -= 1;
      *ball_y += 1;
      *ball_orientation = LEFT_UP;
      break;
    case 14:
      *ball_x -= 1;
      *ball_y -= 1;
      *ball_orientation = LEFT_DOWN;
      break;
  }
}