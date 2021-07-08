#include <ncurses.h>

/* types */
struct Food {
  int x;
  int y;
  int visible;
};

struct Snake {
  int x;
  int y;
  int length;
  // TODO: make snake longer.
};
typedef struct Snake t_snake;

#define GAMEGRID_X 40
#define GAMEGRID_Y 20
#define MOVE_PERIOD 1200 /* In miliseconds. */
#define FOOD_NUM 3

/*Colors:*/
#define C_SNAKE 1
#define C_SNAKE_COLOR COLOR_BLUE

#define C_FOOD 2
#define C_FOOD_COLOR COLOR_GREEN

#define C_OUTER 3
#define C_OUTER_COLOR COLOR_CYAN

#define C_INNERBG 4
#define C_INNERBG_COLOR COLOR_BLACK

#define C_DEBUG 5
#define C_DEBUG_FG COLOR_BLACK
#define C_DEBUG_BG COLOR_RED

#define CHTYPE_OUTER ('X' | A_UNDERLINE| COLOR_PAIR(C_OUTER))
/* Keybindings */
#define KEY_QUIT 'q'

/* global variables */
extern WINDOW *gameWindow;
extern WINDOW *debugWindow;
/* draw functions */
WINDOW *createGameWindow(void);
WINDOW *createDebugWindow(void);
void drawSnake(t_snake *snake);
void drawFood(struct Food foodList[], int foodNum);
void debugText(const char text[], int y);

/* game logic functions */
void generateFood(struct Food foodList[],int foodNum);
void checkFoodCollisions(struct Food foodList[], int foodNum, t_snake *snake, int *score,int *foodRemaining);
void checkSelfCollisions(t_snake *snake);
void moveSnake(t_snake *snake, int dx, int dy);


