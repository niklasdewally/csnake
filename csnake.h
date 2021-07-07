#include <ncurses.h>

#define GAMEGRIDSIZE 20
#define CELLHEIGHT 1
#define CELLWIDTH 2

#define MOVE_PERIOD 0.2 /* In seconds. */

/*Colors:*/
#define C_SNAKE 1
#define C_SNAKE_COLOR COLOR_BLUE

#define C_EDIBLE 2
#define C_EDIBLE_COLOR COLOR_GREEN

#define C_OUTER 3
#define C_OUTER_COLOR COLOR_CYAN

#define C_INNERBG 4
#define C_INNERBG_COLOR COLOR_BLACK

#define CHTYPE_OUTER ('X' | A_UNDERLINE| COLOR_PAIR(C_OUTER))
/* Keybindings */
#define KEY_QUIT 'q'

extern WINDOW *gameWindow;
extern int score;
extern int snakeLength;
extern int gridElementSize;

WINDOW *createGameWindow (void);
void moveSnake (int dx, int dy);
