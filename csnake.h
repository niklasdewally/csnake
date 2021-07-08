#include <ncurses.h>

/* types */
enum DIRECTIONS { NONE, FORWARD, BACK, LEFT, RIGHT };

struct Food {
  int x;
  int y;
  int visible;
};

#define MAX_SNAKE_LENGTH 20
struct Snake {
  int x[MAX_SNAKE_LENGTH];
  int y[MAX_SNAKE_LENGTH];
  int length;
};

typedef struct Snake t_snake;

#define GAMEGRID_X 40
#define GAMEGRID_Y 20
#define MOVE_PERIOD 200 /* In miliseconds. */
#define FOOD_NUM 3

/* colors */
#define C_SNAKE 1
#define C_SNAKE_FG COLOR_BLACK
#define C_SNAKE_BG COLOR_BLUE

#define C_FOOD 2
#define C_FOOD_COLOR COLOR_GREEN

#define C_OUTER 3
#define C_OUTER_COLOR COLOR_CYAN

#define C_INNERBG 4
#define C_INNERBG_COLOR COLOR_BLACK

#define C_DEBUG 5
#define C_DEBUG_FG COLOR_BLACK
#define C_DEBUG_BG COLOR_RED

/* keybindings */
#define K_QUIT 'q'
#define K_RESTART 'r'

/* variables */
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
void checkFoodCollisions(struct Food foodList[], int foodNum, t_snake *snake, int *score,int *foodRemaining, enum DIRECTIONS direction);
int isSelfCollision(t_snake *snake);
void moveSnake(t_snake *snake, int dx, int dy);
void resolveDirections(enum DIRECTIONS direction,int *dx, int *dy);


