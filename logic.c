#include "csnake.h"
#include <curses.h>
#include <stdlib.h>


void generateFood(struct Food foodList[], int foodNum) {
  int  maxx,maxy,minx,miny;

  for (int i=0;i<foodNum;i++){
    /* From https://bytefreaks.net/programming-2/cc-get-a-random-number-that-is-in-a-specific-range  */
    foodList[i].x = (rand() % (GAMEGRID_X - 1) );
    foodList[i].y = (rand() % (GAMEGRID_Y -1) );
    foodList[i].visible = 1;

  }
}

void checkFoodCollisions(struct Food foodList[], int foodNum, t_snake *snake, int *score,int *foodRemaining) {
  int i,j;
  for (i=0;i<foodNum;i++)
    {
    if (foodList[i].x == snake->x && foodList[i].y == snake->y)
      {
        foodList[i].visible = 0;
        *score += 1;
        *foodRemaining -= 1;
        snake->length += 1;
        break;
      }
    }
}

void checkSelfCollisions(t_snake *snake) {
  // TODO: implement checkSelfCollisions
  ;
}

void moveSnake(t_snake *snake,int dx,int dy){
  snake->x += dx;
  snake->y += dy;
}
