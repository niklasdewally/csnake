#include "csnake.h"

int inBounds (int x, int y);

int height,width,starty,startx;
WINDOW *createGameWindow (void) {
  WINDOW *localWindow;

  height = CELLHEIGHT*GAMEGRIDSIZE;
  width = CELLWIDTH*GAMEGRIDSIZE;
  starty = (LINES- height)/2;
  startx = (COLS - width)/2;

  localWindow = newwin(height,width,starty,startx);
  box(localWindow,0,0); /*Create a border with default characters*/
  wrefresh(localWindow); /*Show the border*/
  return localWindow;
}

void moveSnake(int dx, int dy){
  int x,y;
  getyx(gameWindow,y,x);
  if (inBounds(y+dy,x+dx)) {
    werase(gameWindow);
    wattron(gameWindow,COLOR_PAIR(C_SNAKE));
    mvwaddch(gameWindow,y+dy,x+dx-1,'0');
    wattroff(gameWindow,COLOR_PAIR(C_SNAKE));
  }
}

int inBounds(int y, int x){
  return 1;
}
