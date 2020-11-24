#include "head.h"
#define DEMO_MENU


int is_ui = 1;
int to_play_game=0;
extern int is_continue;
extern int username;
extern int is_stop ;
extern void show_score(void);
extern void user(void);

void display_ui(); // 刷新显示
void DisplayClear(void);

void MouseEventProcess_ui(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI获取鼠标
	display_ui(); // 刷新显示
}
void KeyboardEventProcess_ui(int key, int event)
{
	uiGetKeyboard(key, event); // GUI获取键盘
	display_ui(); // 刷新显示
}
 
void Main(void)
{
	SetWindowSize(Slength/1.1, Slength);
	InitGraphics();
	FILE *file_;
	main_ui();
	file_ = fopen(".\\数据\\now_userid.txt", "r");
	fscanf(file_, "%d", &username);
	fclose(file_);
}

#if defined(DEMO_BUTTON)
void main_ui(void)
{	
	SetWindowSize(Slength, Slength);

	InitGraphics();

	SetWindowTitle("俄罗斯方块");	

	drawMenu();

	SetPenColor("Red");
	drawLabel(Slength / 2.6,  Slength* 0.8, "俄罗斯方块");

	SetPenSize(1);

	registerMouseEvent(MouseEventProcess_ui);
	if (button(GenUIID(0), Slength / 3, 20 * Slength / 30, Slength / 5, Slength / 15, "开始游戏")) {
		is_ui = 0;
		is_continue = 0;
		to_play_game = 1;
		is_stop = 0;
	}
	if (button(GenUIID(0), Slength / 3, 17 * Slength / 30, Slength / 5, Slength / 15, "继续游戏")) {
		is_ui = 0;
		is_continue = 1;
		to_play_game = 1;
		is_stop = 0;
	}
	if (button(GenUIID(0), Slength / 3, 14 * Slength / 30, Slength / 5, Slength / 15, "帮助")) {
		MessageBox(NULL, TEXT("在开始界面中选择按键，进入游戏。\n使用键盘的左右键移动下落的物块，向上键翻转物块，向下键加速物块下落。\n可以选择不同难度改变下落速度。\n可以通过菜单栏或者快捷键的方式控制游戏进程，查看排行榜。"), TEXT("使用方法"), MB_OK);
	}
	if (button(GenUIID(0), Slength / 3, 8 * Slength / 30, Slength / 5, Slength / 15, "结束游戏")) {
		ExitGraphics();
	}
	if (button(GenUIID(0), Slength / 3, 11* Slength / 30, Slength / 5, Slength / 15, "用户")) {
		is_ui = 0;
		user();
	}
	is_ui = 1;
	if (to_play_game == 1)
	{
		game();
	}
}
#endif // #if defined(DEMO_BUTTON)

#if defined(DEMO_MENU)
void drawMenu()
{
	registerKeyboardEvent(KeyboardEventProcess_ui);
	static char * menuListFile[] = { "游戏",
		"开始游戏 | Ctrl-O", 
		"继续游戏 | Ctrl-L",
		"退出游戏 | Ctrl-E" };
	static char * menuListTool[] = { "用户",
		"查看分数 | Ctrl-M" };
	static char * menuListHelp[] = { "帮助",
		"使用方法",
		"关于" };
	static char * selectedLabel = NULL;

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = GetWindowHeight();
	double h = fH * 1.5; // 控件高度
	double w = TextStringWidth(menuListHelp[0]) * 2; // 控件宽度
	double wlist = TextStringWidth(menuListTool[1])*1.2;
	double xindent = GetWindowHeight() / 20; // 缩进
	int    selection;

	drawMenuBar(0, y - h, GetWindowHeight(), h);
	// 游戏 菜单
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection > 0) selectedLabel = menuListFile[selection];
	if (selection == 1) {
		is_ui = 0;
		is_continue = 0;
		to_play_game = 1;
		is_stop = 0;
	};
	if (selection == 2) {
		is_ui = 0;
		is_continue = 1;
		to_play_game = 1;
		is_stop = 0;
	}
	if (selection == 3)
		exit(-1); // choose to exit

	// 用户 菜单

	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListTool, sizeof(menuListTool) / sizeof(menuListTool[0]));
	if (selection > 0) selectedLabel = menuListTool[selection];
	if (selection == 1) {
		show_score();
	}

	// 帮助 菜单

	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection > 0) selectedLabel = menuListHelp[selection];
	//使用方法
	if (selection == 1)
	{
		MessageBox(NULL, TEXT("在开始界面中建立用户，选择不同的难度，进入游戏。\n使用键盘的左右键移动下落的物块，向上键翻转物块，向下键加速物块下落，空格键使物块直接落地。\n可以通过菜单栏或者快捷键的方式控制游戏进程，查看排行榜。"), TEXT("使用方法"), MB_OK);
	}
	//关于
	if (selection == 2)
		MessageBox(NULL, TEXT("课程：程序设计专题\n程序名：俄罗斯方块\n制作人员：北街刷夜大队——吴夏楠 周开宁 邓岚彬\n完成时间：2019年6月"), TEXT("关于"), MB_OK);
	
	if (to_play_game == 1)
	{
		game();
	}
}
#endif // #if defined(DEMO_MENU)

void display_ui()
{
	// 清屏
	DisplayClear();

#if defined(DEMO_MENU)
	// 绘制和处理菜单
	drawMenu();
#endif
	main_ui();
}