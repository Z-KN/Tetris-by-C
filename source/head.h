#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include "imgui.h"

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <time.h>
#include <conio.h>
#include <direct.h>
#include <io.h>


#define Board_X 30
#define Board_Y 30
#define Slength 8.4
#define side 2
#define Left_Down_x 2
#define Left_Down_y 3
#define Left_Up_x 2
#define Left_Up_y 23
#define Right_Down_x 14
#define Right_Down_y 3
#define Right_Up_x 14
#define Right_Up_y 23

#define Board_color 7
#define sidecolor 4

#define FILLED 1
#define EMPTY 0

#define DEMO_BUTTON
#define DEMO_MENU


void drawblock(int shape, int rotate, int x, int y, char *color);
void coverblock(int shape, int rotate, int x, int y, char *color);
int check_bottom(int shape, int rotate, int x, int y);
void init_block_data(void);
void check_clear_line(void);
void clear_line(int line_index, int count);
void add_score(int count);
int check_gameover(void);
void draw_interface(void);
void draw_gameface(void);
void init_gameface(void);
void keyboard_event_process(int key, int event);
void play_game(void);
void gameover(void);
void draw_tool(void);
void mouse_event_process(int mouse_x, int mouxe_y, int button, int event);
void stop(void);
void start(void);
void restart(void);
void end(void);
void back(void);
char *num2str(int num);
void game(void);
void user_ui(void);
void save(void);
void create_user(void);
void remove_user(void);
void change_user(void);
void rank(void);
void show_score(void);
void main_ui(void);
void user(void);
void DisplayClear(void);
void drawMenu();