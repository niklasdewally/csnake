#include "csnake.h"
#include <curses.h>
#include <stdio.h>
#include <time.h>

enum DIRECTIONS {FORWARD,BACK,LEFT,RIGHT} direction = FORWARD;

WINDOW *gameWindow;
WINDOW *debugWindow;

t_snake snake;
struct Food foodList[FOOD_NUM];
int score,foodRemaining;

void doGameTick(enum DIRECTIONS direction);

int main(void){
  int ch;
  WINDOW *parentWindow = initscr();

  start_color();
  init_pair(C_SNAKE,C_SNAKE_COLOR,C_SNAKE_COLOR);
  init_pair(C_FOOD,C_FOOD_COLOR,C_FOOD_COLOR);
  init_pair(C_OUTER,C_OUTER_COLOR,C_OUTER_COLOR);
  init_pair(C_INNERBG,C_INNERBG_COLOR,C_INNERBG_COLOR);
  init_pair(C_DEBUG, C_DEBUG_FG, C_DEBUG_BG);

  raw(); /* Disables line buffering - gives us user-input immediately */
  keypad(stdscr,TRUE); /* Allow reading of function keys / arrow keys */
  noecho();
  nodelay(parentWindow,TRUE); /* Make getch a non-blocking call - returns ERR if no input is given */

  curs_set(0);
  refresh();
  bkgd(COLOR_PAIR(C_OUTER)); /* Background color! */

  gameWindow = createGameWindow();
  debugWindow = createDebugWindow();
  wbkgd(gameWindow,COLOR_PAIR(C_INNERBG));

  /* == GAME VARIABLES ==  */
  score = 0;
  snake.x = 1;
  snake.y = 1;
  snake.length = 1;
  generateFood(foodList,FOOD_NUM);
  foodRemaining = FOOD_NUM;

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
    char text4[150];
    if ((dtime = difftime(currTime,lastTime)) >= MOVE_PERIOD){
        /*Update lastTime */
        lastTime = currTime;
        doGameTick(direction);
        sprintf(text4,"Time: %2.5f",dtime);
        debugText(text4,3);
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
  moveSnake(&snake,dx,dy);
  checkFoodCollisions(foodList,FOOD_NUM,&snake,&score,&foodRemaining);
  if (foodRemaining==0){
    generateFood(foodList,FOOD_NUM);
    foodRemaining = FOOD_NUM;
  }
  checkSelfCollisions(&snake);

  /* == DRAWING ==  */
  char text1[20],text2[20],text3[150];
  sprintf(text1,"foodRemaining: %d",foodRemaining);
  sprintf(text2,"score: %d",score);
  sprintf(text3,"food1: %d %d food2: %d %d food3: %d %d",foodList[0].x,foodList[0].y,foodList[1].x,foodList[1].y,foodList[2].x,foodList[2].y);
  debugText(text1,0);
  debugText(text2,1);
  debugText(text3,2);

  werase(gameWindow);
  drawSnake(&snake);
  drawFood(foodList,FOOD_NUM);
  wrefresh(gameWindow);
}
