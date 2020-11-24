#include "head.h"
#define DEMO_MENU


int is_ui = 1;
int to_play_game=0;
extern int is_continue;
extern int username;
extern int is_stop ;
extern void show_score(void);
extern void user(void);

void display_ui(); // ˢ����ʾ
void DisplayClear(void);

void MouseEventProcess_ui(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI��ȡ���
	display_ui(); // ˢ����ʾ
}
void KeyboardEventProcess_ui(int key, int event)
{
	uiGetKeyboard(key, event); // GUI��ȡ����
	display_ui(); // ˢ����ʾ
}
 
void Main(void)
{
	SetWindowSize(Slength/1.1, Slength);
	InitGraphics();
	FILE *file_;
	main_ui();
	file_ = fopen(".\\����\\now_userid.txt", "r");
	fscanf(file_, "%d", &username);
	fclose(file_);
}

#if defined(DEMO_BUTTON)
void main_ui(void)
{	
	SetWindowSize(Slength, Slength);

	InitGraphics();

	SetWindowTitle("����˹����");	

	drawMenu();

	SetPenColor("Red");
	drawLabel(Slength / 2.6,  Slength* 0.8, "����˹����");

	SetPenSize(1);

	registerMouseEvent(MouseEventProcess_ui);
	if (button(GenUIID(0), Slength / 3, 20 * Slength / 30, Slength / 5, Slength / 15, "��ʼ��Ϸ")) {
		is_ui = 0;
		is_continue = 0;
		to_play_game = 1;
		is_stop = 0;
	}
	if (button(GenUIID(0), Slength / 3, 17 * Slength / 30, Slength / 5, Slength / 15, "������Ϸ")) {
		is_ui = 0;
		is_continue = 1;
		to_play_game = 1;
		is_stop = 0;
	}
	if (button(GenUIID(0), Slength / 3, 14 * Slength / 30, Slength / 5, Slength / 15, "����")) {
		MessageBox(NULL, TEXT("�ڿ�ʼ������ѡ�񰴼���������Ϸ��\nʹ�ü��̵����Ҽ��ƶ��������飬���ϼ���ת��飬���¼�����������䡣\n����ѡ��ͬ�Ѷȸı������ٶȡ�\n����ͨ���˵������߿�ݼ��ķ�ʽ������Ϸ���̣��鿴���а�"), TEXT("ʹ�÷���"), MB_OK);
	}
	if (button(GenUIID(0), Slength / 3, 8 * Slength / 30, Slength / 5, Slength / 15, "������Ϸ")) {
		ExitGraphics();
	}
	if (button(GenUIID(0), Slength / 3, 11* Slength / 30, Slength / 5, Slength / 15, "�û�")) {
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
	static char * menuListFile[] = { "��Ϸ",
		"��ʼ��Ϸ | Ctrl-O", 
		"������Ϸ | Ctrl-L",
		"�˳���Ϸ | Ctrl-E" };
	static char * menuListTool[] = { "�û�",
		"�鿴���� | Ctrl-M" };
	static char * menuListHelp[] = { "����",
		"ʹ�÷���",
		"����" };
	static char * selectedLabel = NULL;

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = GetWindowHeight();
	double h = fH * 1.5; // �ؼ��߶�
	double w = TextStringWidth(menuListHelp[0]) * 2; // �ؼ����
	double wlist = TextStringWidth(menuListTool[1])*1.2;
	double xindent = GetWindowHeight() / 20; // ����
	int    selection;

	drawMenuBar(0, y - h, GetWindowHeight(), h);
	// ��Ϸ �˵�
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

	// �û� �˵�

	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListTool, sizeof(menuListTool) / sizeof(menuListTool[0]));
	if (selection > 0) selectedLabel = menuListTool[selection];
	if (selection == 1) {
		show_score();
	}

	// ���� �˵�

	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection > 0) selectedLabel = menuListHelp[selection];
	//ʹ�÷���
	if (selection == 1)
	{
		MessageBox(NULL, TEXT("�ڿ�ʼ�����н����û���ѡ��ͬ���Ѷȣ�������Ϸ��\nʹ�ü��̵����Ҽ��ƶ��������飬���ϼ���ת��飬���¼�����������䣬�ո��ʹ���ֱ����ء�\n����ͨ���˵������߿�ݼ��ķ�ʽ������Ϸ���̣��鿴���а�"), TEXT("ʹ�÷���"), MB_OK);
	}
	//����
	if (selection == 2)
		MessageBox(NULL, TEXT("�γ̣��������ר��\n������������˹����\n������Ա������ˢҹ��ӡ�������� �ܿ��� ��ᰱ�\n���ʱ�䣺2019��6��"), TEXT("����"), MB_OK);
	
	if (to_play_game == 1)
	{
		game();
	}
}
#endif // #if defined(DEMO_MENU)

void display_ui()
{
	// ����
	DisplayClear();

#if defined(DEMO_MENU)
	// ���ƺʹ���˵�
	drawMenu();
#endif
	main_ui();
}