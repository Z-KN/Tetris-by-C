#include "head.h"

extern int username;
extern int is_ui;

int max_user = 1;//分数最高的用户
int count = 1;//计数

FILE *max;//指向最高得分文件的指针
FILE *COUNT;//指向计数文件指针
FILE *now_user;//指向当前用户的指针

void BubbleSort(struct users_information *head);
void display_userui();
void MouseEventProcess_userui(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI获取鼠标
	display_userui(); // 刷新显示
}

struct users_information
{
	int user_num;
	int score;
	char name[20];
	struct users_information *next;
}*head, *p, *q, *t;

void user(void)
{
	user_ui();
	max = fopen(".\\数据\\max.txt", "r");
	fscanf(max, "%d", &max_user);
	fclose(max);
	COUNT = fopen(".\\数据\\count.txt", "r");
	fscanf(COUNT, "%d", &count);
	fclose(COUNT);


	now_user = fopen(".\\数据\\now_userid.txt", "r");
	fscanf(now_user, "%d", &username);
	fclose(now_user);
	save();
}

#if defined(DEMO_BUTTON)
void user_ui(void)
{

	InitGraphics();
	SetWindowSize(Slength, Slength);
	SetPenColor("Red");
	drawLabel(Slength / 2.6, Slength* 0.8, "俄罗斯方块");

	drawMenu();
	SetPenColor("Black");
	SetPenSize(1);

	registerMouseEvent(MouseEventProcess_userui);

	if (button(GenUIID(0), Slength / 3, 20 * Slength / 30, Slength / 5, Slength / 15, "创建用户")) {
		create_user();
	}
	if (button(GenUIID(0), Slength / 3, 17 * Slength / 30, Slength / 5, Slength / 15, "删除用户")) {
		remove_user();
	}
	if (button(GenUIID(0), Slength / 3, 14 * Slength / 30, Slength / 5, Slength / 15, "切换用户")) {
		change_user();
	}
	if (button(GenUIID(0), Slength / 3, 11 * Slength / 30, Slength / 5, Slength / 15, "排 行 榜")) {
		rank();
	}
	if (button(GenUIID(0), Slength / 3, 8 * Slength / 30, Slength / 5, Slength / 15, "查看分数")) {
		show_score();
	}
	if (button(GenUIID(0), Slength / 3, 5 * Slength / 30, Slength / 5, Slength / 15, "返    回")) {
		is_ui = 1;
		main_ui();
	}

}
#endif // #if defined(DEMO_BUTTON)
void display_userui()
{
	// 清屏
	DisplayClear();

#if defined(DEMO_MENU)
	// 绘制和处理菜单
	drawMenu();
#endif
	user_ui();
}
void save(void)
{
	FILE *file;
	int i = 2;
	head = (struct users_information*)malloc(sizeof(struct users_information));
	file = fopen(".\\数据\\user1_name.txt", "r");
	fscanf(file, "%s", head->name);
	fclose(file);
	file = fopen(".\\数据\\user1_score.txt", "r");
	fscanf(file, "%d", &head->score);
	fclose(file);
	head->user_num = 1;
	head->next = NULL;
	p = head;
	for (i = 2; i <= max_user; i++)
	{
		char filename1[40];
		strcpy(filename1, ".\\数据\\user");
		char *user_id1 = (char *)malloc(sizeof(char) * 6);
		strcpy(user_id1, num2str(i));
		strcat(filename1, user_id1);
		strcat(filename1, "_name.txt");
		file = fopen(filename1, "r");
		if (file == NULL)
			continue;
		else
		{
			p->next = (struct users_information*)malloc(sizeof(struct users_information));
			p->next->user_num = i;
			fscanf(file, "%s", p->next->name);
			fclose(file);

			char filename2[40];
			strcpy(filename2, ".\\数据\\user");
			char *user_id2 = (char *)malloc(sizeof(char) * 6);
			strcpy(user_id2, num2str(i));
			strcat(filename2, user_id2);
			strcat(filename2, "_score.txt");
			file = fopen(filename2, "r");
			fscanf(file, "%d", &p->next->score);
			fclose(file);
			p->next->next = NULL;
			p = p->next;
		}
	}
}

void traversal_data(void)
{
	p = head;
	while (p->next)
		p = p->next;
}

void create_user(void)
{
	FILE *file;
	char filename1[40], filename2[40], filename3[40];
	InitConsole();
	printf("输入您要创建的用户名：\n");
	char s[40];
	scanf("%s", s);

	traversal_data();
	p->next = (struct users_information*)malloc(sizeof(struct users_information));
	p->next->user_num = max_user + 1;
	p->next->score = 0;
	strcpy(p->next->name, s);

	strcpy(filename1, ".\\数据\\user");
	char *user_id1 = (char *)malloc(sizeof(char) * 6);
	strcpy(user_id1, num2str(p->next->user_num));
	strcat(filename1, user_id1);
	strcat(filename1, "_name.txt");
	file = fopen(filename1, "w");
	fprintf(file, "%s", p->next->name);
	fclose(file);

	strcpy(filename2, ".\\数据\\user");
	char *user_id2 = (char *)malloc(sizeof(char) * 6);
	strcpy(user_id2, num2str(p->next->user_num));
	strcat(filename2, user_id2);
	strcat(filename2, "_score.txt");
	file = fopen(filename2, "w");
	int a = 0;
	fprintf(file, "%d", a);
	fclose(file);


	strcpy(filename3, ".\\数据\\user");
	char *user_id3 = (char *)malloc(sizeof(char) * 6);
	strcpy(user_id3, num2str(p->next->user_num));
	strcat(filename3, user_id3);
	strcat(filename3, "_game.txt");
	file = fopen(filename3, "w");
	fclose(file);

	count++;
	max_user++;
	max = fopen(".\\数据\\max.txt", "w");
	if (fprintf(max, "%d", max_user))
		fclose(max);
	COUNT = fopen(".\\数据\\count.txt", "w");
	fprintf(COUNT, "%d", count);
	fclose(COUNT);
	save();
	printf("创建用户成功。\n如果要以您现在创建的用户名进行游戏，请在关闭本窗口后点“切换用户”进行当前用户切换。");
	FreeConsole();
}
void remove_user(void)
{
	int i = 1;
	int input;
	InitConsole();
	printf("请输入要删除用户的序号：\n");
	p = head;
	while (p->next != NULL)
	{
		printf("%d\t%s\n", i++, p->next->name);
		p = p->next;
	}
	scanf("%d", &input);
	if (input < i)
	{
		p = head;
		for (i = 0; i < input - 1; i++)
			p = p->next;
		if (p->next->user_num == username)
		{
			MessageBox(NULL, "不能删除正在运行的用户，请再次尝试。", "waring", NULL);
		}
		else
		{
			char filename1[40];
			strcpy(filename1, ".\\数据\\user");
			char *user_id1 = (char *)malloc(sizeof(char) * 6);
			strcpy(user_id1, num2str(p->next->user_num));
			strcat(filename1, user_id1);
			strcat(filename1, "_name.txt");
			remove(filename1);
			char filename2[40];
			strcpy(filename2, ".\\数据\\user");
			char *user_id2 = (char *)malloc(sizeof(char) * 6);
			strcpy(user_id2, num2str(p->next->user_num));
			strcat(filename2, user_id2);
			strcat(filename2, "_score.txt");
			remove(filename2);
			char filename3[40];
			strcpy(filename3, ".\\数据\\user");
			char *user_id3 = (char *)malloc(sizeof(char) * 6);
			strcpy(user_id3, num2str(p->next->user_num));
			strcat(filename3, user_id3);
			strcat(filename3, "_game.txt");
			remove(filename3);

			count--;
			COUNT = fopen(".\\数据\\count.txt", "w");
			fprintf(COUNT, "%d", count);
			fclose(COUNT);
			save();
			printf("\n删除成功。请关闭此窗口。\n");
			FreeConsole();
		}
	}
	else
	{
		printf("\n用户不存在。\n");
	}
	FreeConsole();
}
void change_user(void)
{
	int i = 1;
	int input;
	InitConsole();
	printf("请输入要切换的用户的序号：\n");
	p = head;
	while (p->next != NULL)
	{
		printf("%d\t%s\n", i++, p->next->name);
		p = p->next;
	}
	scanf("%d", &input);
	if (input < i)
	{
		p = head;
		for (i = 0; i < input - 1; i++)
			p = p->next;

		username = p->next->user_num;
		now_user = fopen(".\\数据\\now_userid.txt", "w");
		fprintf(now_user, "%d", username);
		fclose(now_user);
		printf("切换成功，请关闭此窗口。\n");
		FreeConsole();
	}
}

void rank(void)
{
	BubbleSort(head);

	InitConsole();
	printf("排行榜：\n");
	printf("用户名\t\t\t\t最高得分\n");
	p = head;
	while (p)
	{
		printf("%-20s\t\t%d\n\n", p->name, p->score);
		p = p->next;
	}
	printf("请关闭此窗口。\n");
	FreeConsole();
}
void show_score(void)
{
	int temp_score = 0;
	char temp_name[40], filename1[40], filename2[40];
	FILE *temp;


	strcpy(filename1, ".\\数据\\user");
	char *user_id1 = (char *)malloc(sizeof(char) * 6);
	strcpy(user_id1, num2str(username));
	strcat(filename1, user_id1);
	strcat(filename1, "_name.txt");
	temp = fopen(filename1, "r");
	fscanf(temp, "%s", temp_name);
	fclose(temp);


	strcpy(filename2, ".\\数据\\user");
	char *user_id2 = (char *)malloc(sizeof(char) * 6);
	strcpy(user_id2, num2str(username));
	strcat(filename2, user_id2);
	strcat(filename2, "_score.txt");
	temp = fopen(filename2, "r");
	fscanf(temp, "%d", &temp_score);
	fclose(temp);

	InitConsole();
	printf("当前用户信息：\n");
	printf("用户名       最高得分\n");
	printf("%s\t%d\n", temp_name, temp_score);
	printf("\n请关闭此窗口。\n");
	FreeConsole();
}

void BubbleSort(struct users_information *head) {
	struct users_information *cur, *tail;
	int temp,temp1;
	cur = head;
	tail = NULL;
	if (cur == NULL || cur->next == NULL) return;
	while (cur != tail) {
		while (cur->next != tail) {
			if (cur->score < cur->next->score) {
				temp = cur->score;
				cur->score = cur->next->score;
				cur->next->score = temp;
				temp1 = cur->user_num;
				cur->user_num = cur->next->user_num;
				cur->next->user_num = temp1;
			}
			cur = cur->next;
		}
		tail = cur;
		cur = head;
	}
}