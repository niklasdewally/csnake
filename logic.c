#include "csnake.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

void extendSnake(t_snake * , enum DIRECTIONS);

void generateFood(struct Food foodList[], int foodNum) {
  int  maxx,maxy,minx,miny;

  for (int i=0;i<foodNum;i++){
    /* From https://bytefreaks.net/programming-2/cc-get-a-random-number-that-is-in-a-specific-range  */
    foodList[i].x = (rand() % (GAMEGRID_X - 1) );
    foodList[i].y = (rand() % (GAMEGRID_Y -1) );
    foodList[i].visible = 1;

  }
}

void checkFoodCollisions(struct Food foodList[], int foodNum, t_snake *snake, int *score, int *foodRemaining, enum DIRECTIONS direction) {
  int i,j;
  for (i=0;i<foodNum;i++)
    {
    if (foodList[i].x == snake->x[0] && foodList[i].y == snake->y[0])
      {
        foodList[i].visible = 0;
        *score += 1;
        *foodRemaining -= 1;
        extendSnake(snake, direction);
        break;
      }
    }
}

int isSelfCollision(t_snake *snake) {
  int i,j;
  for (i=0;i<snake->length;i++){
    for (j=i+1;j<snake->length;j++){
      if(snake->x[i]==snake->x[j] && snake->y[i]==snake->y[j]){
        return 1;
      }
    }
  }
  return 0;
}

int isWallCollision(t_snake *snake){
  if (snake->x[0] < 0 || snake->x[0] >= GAMEGRID_X || snake->y[0] < 0 || snake->y[0] >= GAMEGRID_Y ){
    return 1;
  }
  return 0;
}

void moveSnake(t_snake *snake,int dx,int dy){
  /* Copying the entire array is a dumb implementation, but i'm dumb */
  int ax[MAX_SNAKE_LENGTH],ay[MAX_SNAKE_LENGTH];
  /*Copy the array - BAD! */
  for (int i = 0; i < MAX_SNAKE_LENGTH; i++) {
    ax[i] = snake->x[i];
    ay[i] = snake->y[i];
  }
  /* Sort out the indexes */
  snake->x[0] += dx;
  snake->y[0] += dy;
  for (int i = 1; i < snake->length;i++){
    snake->x[i] = ax[i-1];
    snake->y[i] = ay[i-1];
  }
}

void extendSnake(t_snake *snake,enum DIRECTIONS direction){
  int newdx,newdy,newx,newy;

  if (snake->length==1){
    resolveDirections(direction, &newdx, &newdy);
  }
  else {
    newdx = snake->x[snake->length - 1] - snake->x[snake->length - 2];
    newdy = snake->y[snake->length - 1] - snake->y[snake->length - 2];
  }
  char debugtext[100],debugtext2[100];
  sprintf(debugtext, "newdx:%d,newdy:%d", newdx, newdy);
  debugText(debugtext, 8);

  snake->x[snake->length] = snake->x[snake->length-1] + newdx;
  snake->y[snake->length] = snake->y[snake->length-1] + newdy;
  snake->length += 1;
}

void resolveDirections(enum DIRECTIONS direction, int *dx, int *dy) {
  *dx = 0;
  *dy = 0;
  switch (direction) {
  case NONE:
    break;
  case FORWARD:
    *dy = -1;
    break;
  case BACK:
    *dy = 1;
    break;
  case LEFT:
    *dx = -1;
    break;
  case RIGHT:
    *dx = 1;
    break;
  }
}
