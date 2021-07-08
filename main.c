#include "csnake.h"
#include <bits/time.h>
#include <curses.h>
#include <time.h>

enum DIRECTIONS direction = NONE;
WINDOW *gameWindow;
WINDOW *debugWindow;

t_snake snake;
struct Food foodList[FOOD_NUM];
int score,foodRemaining;

void initGame(void);
void doGameTick(enum DIRECTIONS direction);
double timetomili(struct timespec *times);

int main(void){
  int ch;
  WINDOW *parentWindow = initscr();

  start_color();
  init_pair(C_SNAKE,C_SNAKE_FG,C_SNAKE_BG);
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

  initGame();

  struct timespec lastTime,currTime;
  double dtime;
  clock_gettime(CLOCK_MONOTONIC,&lastTime);
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
        if (direction != BACK){
          direction = FORWARD;
        }
        break;
      case 's':
        if (direction != FORWARD){
          direction = BACK;
        }
        break;
      case 'a':
        if (direction != RIGHT){
          direction = LEFT;
        }
        break;
      case 'd':
        if (direction != LEFT){
        direction = RIGHT;
        }
        break;
      }
  /* Do stuff every MOVE_PERIOD */
    clock_gettime(CLOCK_MONOTONIC,&currTime);
    char text4[150];
    if ((dtime = timetomili(&currTime)- timetomili(&lastTime)) >= MOVE_PERIOD){
        /*Update lastTime - I could do this with pointers if i knew how to use them!
         * It seems here that i would need an infinite number of new variables to point to, which is annoying!
         */
      clock_gettime(CLOCK_MONOTONIC,&lastTime);
      doGameTick(direction);
      sprintf(text4, "Last Tick Time: %4.2f", dtime);
      debugText(text4, 3);
    }

  }
  endwin();
  return 0;
}

void initGame(void){
  score = 0;
  snake.x[0] = 1;
  snake.y[0] = 1;
  snake.length = 1;
  generateFood(foodList, FOOD_NUM);
  foodRemaining = FOOD_NUM;
}

void doGameTick(enum DIRECTIONS direction) {
  int dx,dy;
  resolveDirections(direction,&dx,&dy);

  moveSnake(&snake,dx,dy);
  
  checkFoodCollisions(foodList,FOOD_NUM,&snake,&score,&foodRemaining,direction);
  if (foodRemaining==0){
    generateFood(foodList,FOOD_NUM);
    foodRemaining = FOOD_NUM;
  }

  if (isSelfCollision(&snake)){
    // Game Over
    initGame();
     return;
  }

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


double timetomili(struct timespec *timesp){
  return (timesp->tv_sec)*1000 + (double) (timesp->tv_nsec)/1000000; 
}

