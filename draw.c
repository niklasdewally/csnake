#include "csnake.h"
#include <curses.h>
#include <stdlib.h>

int height,width,starty,startx;
WINDOW *createGameWindow (void) {
  WINDOW *localWindow;

  height = GAMEGRID_Y;
  width = GAMEGRID_X;
  starty = (LINES- height)/2;
  startx = (COLS - width)/2;

  localWindow = newwin(height,width,starty,startx);
  box(localWindow,0,0); /*Create a border with default characters*/
  wrefresh(localWindow); /*Show the border*/
  return localWindow;
}

WINDOW *createDebugWindow (void){
  WINDOW *localWindow;
  localWindow = newwin(5, COLS, 0, 0);
  wrefresh(localWindow);
  return localWindow;
}

void drawSnake(t_snake *snake){
  wattron(gameWindow,COLOR_PAIR(C_SNAKE));
  mvwaddch(gameWindow,snake->y,snake->x,'0');
  wattroff(gameWindow,COLOR_PAIR(C_SNAKE));
  }

void drawFood(struct Food foodList[], int foodNum){
  wattron(gameWindow,COLOR_PAIR(C_FOOD));
  int i;
  for (i=0;i<foodNum;i++){
    if (foodList[i].visible)
      mvwaddch(gameWindow,foodList[i].y,foodList[i].x,'F');
  }
  wattroff(gameWindow,COLOR_PAIR(C_FOOD));
}

void debugText(const char text[],int y){
  /* Use sprintf() to create formatted text to give to this function for processing */
  attron(COLOR_PAIR(C_DEBUG));
  mvaddstr(y,0,text);
  attroff(COLOR_PAIR(C_DEBUG));
  wrefresh(debugWindow);
}
