#include "csnake.h"
#include <time.h>

enum DIRECTIONS {FORWARD,BACK,LEFT,RIGHT} direction = FORWARD;
WINDOW *gameWindow;

void doGameTick(enum DIRECTIONS direction);

int main(void){
  int ch;
  WINDOW *parentWindow = initscr();

  start_color();
  init_pair(C_SNAKE,C_SNAKE_COLOR,C_SNAKE_COLOR);
  init_pair(C_EDIBLE,C_EDIBLE_COLOR,C_EDIBLE_COLOR);
  init_pair(C_OUTER,C_OUTER_COLOR,C_OUTER_COLOR);
  init_pair(C_INNERBG,C_INNERBG_COLOR,C_INNERBG_COLOR);

  raw(); /* Disables line buffering - gives us user-input immediately */
  keypad(stdscr,TRUE); /* Allow reading of function keys / arrow keys */
  noecho();
  nodelay(parentWindow,TRUE); /* Make getch a non-blocking call - returns ERR if no input is given */

  curs_set(0);
  refresh();
  bkgd(COLOR_PAIR(C_OUTER)); /* Background color! */

  gameWindow = createGameWindow();

  wbkgd(gameWindow,COLOR_PAIR(C_INNERBG));
  time_t lastTime,currTime;
  double dtime;
  lastTime = time(NULL);
  /* Game Loop! */
  while ((ch=getch()) != KEY_QUIT){
    /* Process Input */
    switch (ch)
      {
      default:
        break;
      case ERR: /* No input! */
        break;
      case 'w':
        direction = FORWARD;
        break;
      case 's':
        direction = BACK;
        break;
      case 'a':
        direction = LEFT;
        break;
      case 'd':
        direction = RIGHT;
        break;
      }

    /* Do stuff every MOVE_PERIOD */
    currTime = time(NULL);
    if ((dtime = difftime(currTime,lastTime)) >= MOVE_PERIOD){
        /*Update lastTime */
        lastTime = currTime;
        doGameTick(direction);
    }
  }
  endwin();
  return 0;
}

void doGameTick(enum DIRECTIONS direction) {
  int dx,dy;
  dx = 0;
  dy = 0;
  switch (direction)
    {
    case FORWARD:
      dy = -1;
      break;
    case BACK:
      dy = 1;
      break;
    case LEFT:
      dx=-1;
      break;
    case RIGHT:
      dx=1;
      break;
  }
  moveSnake(dx,dy);
  wrefresh(gameWindow);
  ;}
