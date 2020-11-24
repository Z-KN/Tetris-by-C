#include "head.h"

extern int username;
extern int is_ui;

int max_user = 1;//������ߵ��û�
int count = 1;//����

FILE *max;//ָ����ߵ÷��ļ���ָ��
FILE *COUNT;//ָ������ļ�ָ��
FILE *now_user;//ָ��ǰ�û���ָ��

void BubbleSort(struct users_information *head);
void display_userui();
void MouseEventProcess_userui(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI��ȡ���
	display_userui(); // ˢ����ʾ
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
	max = fopen(".\\����\\max.txt", "r");
	fscanf(max, "%d", &max_user);
	fclose(max);
	COUNT = fopen(".\\����\\count.txt", "r");
	fscanf(COUNT, "%d", &count);
	fclose(COUNT);


	now_user = fopen(".\\����\\now_userid.txt", "r");
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
	drawLabel(Slength / 2.6, Slength* 0.8, "����˹����");

	drawMenu();
	SetPenColor("Black");
	SetPenSize(1);

	registerMouseEvent(MouseEventProcess_userui);

	if (button(GenUIID(0), Slength / 3, 20 * Slength / 30, Slength / 5, Slength / 15, "�����û�")) {
		create_user();
	}
	if (button(GenUIID(0), Slength / 3, 17 * Slength / 30, Slength / 5, Slength / 15, "ɾ���û�")) {
		remove_user();
	}
	if (button(GenUIID(0), Slength / 3, 14 * Slength / 30, Slength / 5, Slength / 15, "�л��û�")) {
		change_user();
	}
	if (button(GenUIID(0), Slength / 3, 11 * Slength / 30, Slength / 5, Slength / 15, "�� �� ��")) {
		rank();
	}
	if (button(GenUIID(0), Slength / 3, 8 * Slength / 30, Slength / 5, Slength / 15, "�鿴����")) {
		show_score();
	}
	if (button(GenUIID(0), Slength / 3, 5 * Slength / 30, Slength / 5, Slength / 15, "��    ��")) {
		is_ui = 1;
		main_ui();
	}

}
#endif // #if defined(DEMO_BUTTON)
void display_userui()
{
	// ����
	DisplayClear();

#if defined(DEMO_MENU)
	// ���ƺʹ���˵�
	drawMenu();
#endif
	user_ui();
}
void save(void)
{
	FILE *file;
	int i = 2;
	head = (struct users_information*)malloc(sizeof(struct users_information));
	file = fopen(".\\����\\user1_name.txt", "r");
	fscanf(file, "%s", head->name);
	fclose(file);
	file = fopen(".\\����\\user1_score.txt", "r");
	fscanf(file, "%d", &head->score);
	fclose(file);
	head->user_num = 1;
	head->next = NULL;
	p = head;
	for (i = 2; i <= max_user; i++)
	{
		char filename1[40];
		strcpy(filename1, ".\\����\\user");
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
			strcpy(filename2, ".\\����\\user");
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
	printf("������Ҫ�������û�����\n");
	char s[40];
	scanf("%s", s);

	traversal_data();
	p->next = (struct users_information*)malloc(sizeof(struct users_information));
	p->next->user_num = max_user + 1;
	p->next->score = 0;
	strcpy(p->next->name, s);

	strcpy(filename1, ".\\����\\user");
	char *user_id1 = (char *)malloc(sizeof(char) * 6);
	strcpy(user_id1, num2str(p->next->user_num));
	strcat(filename1, user_id1);
	strcat(filename1, "_name.txt");
	file = fopen(filename1, "w");
	fprintf(file, "%s", p->next->name);
	fclose(file);

	strcpy(filename2, ".\\����\\user");
	char *user_id2 = (char *)malloc(sizeof(char) * 6);
	strcpy(user_id2, num2str(p->next->user_num));
	strcat(filename2, user_id2);
	strcat(filename2, "_score.txt");
	file = fopen(filename2, "w");
	int a = 0;
	fprintf(file, "%d", a);
	fclose(file);


	strcpy(filename3, ".\\����\\user");
	char *user_id3 = (char *)malloc(sizeof(char) * 6);
	strcpy(user_id3, num2str(p->next->user_num));
	strcat(filename3, user_id3);
	strcat(filename3, "_game.txt");
	file = fopen(filename3, "w");
	fclose(file);

	count++;
	max_user++;
	max = fopen(".\\����\\max.txt", "w");
	if (fprintf(max, "%d", max_user))
		fclose(max);
	COUNT = fopen(".\\����\\count.txt", "w");
	fprintf(COUNT, "%d", count);
	fclose(COUNT);
	save();
	printf("�����û��ɹ���\n���Ҫ�������ڴ������û���������Ϸ�����ڹرձ����ں�㡰�л��û������е�ǰ�û��л���");
	FreeConsole();
}
void remove_user(void)
{
	int i = 1;
	int input;
	InitConsole();
	printf("������Ҫɾ���û�����ţ�\n");
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
			MessageBox(NULL, "����ɾ���������е��û������ٴγ��ԡ�", "waring", NULL);
		}
		else
		{
			char filename1[40];
			strcpy(filename1, ".\\����\\user");
			char *user_id1 = (char *)malloc(sizeof(char) * 6);
			strcpy(user_id1, num2str(p->next->user_num));
			strcat(filename1, user_id1);
			strcat(filename1, "_name.txt");
			remove(filename1);
			char filename2[40];
			strcpy(filename2, ".\\����\\user");
			char *user_id2 = (char *)malloc(sizeof(char) * 6);
			strcpy(user_id2, num2str(p->next->user_num));
			strcat(filename2, user_id2);
			strcat(filename2, "_score.txt");
			remove(filename2);
			char filename3[40];
			strcpy(filename3, ".\\����\\user");
			char *user_id3 = (char *)malloc(sizeof(char) * 6);
			strcpy(user_id3, num2str(p->next->user_num));
			strcat(filename3, user_id3);
			strcat(filename3, "_game.txt");
			remove(filename3);

			count--;
			COUNT = fopen(".\\����\\count.txt", "w");
			fprintf(COUNT, "%d", count);
			fclose(COUNT);
			save();
			printf("\nɾ���ɹ�����رմ˴��ڡ�\n");
			FreeConsole();
		}
	}
	else
	{
		printf("\n�û������ڡ�\n");
	}
	FreeConsole();
}
void change_user(void)
{
	int i = 1;
	int input;
	InitConsole();
	printf("������Ҫ�л����û�����ţ�\n");
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
		now_user = fopen(".\\����\\now_userid.txt", "w");
		fprintf(now_user, "%d", username);
		fclose(now_user);
		printf("�л��ɹ�����رմ˴��ڡ�\n");
		FreeConsole();
	}
}

void rank(void)
{
	BubbleSort(head);

	InitConsole();
	printf("���а�\n");
	printf("�û���\t\t\t\t��ߵ÷�\n");
	p = head;
	while (p)
	{
		printf("%-20s\t\t%d\n\n", p->name, p->score);
		p = p->next;
	}
	printf("��رմ˴��ڡ�\n");
	FreeConsole();
}
void show_score(void)
{
	int temp_score = 0;
	char temp_name[40], filename1[40], filename2[40];
	FILE *temp;


	strcpy(filename1, ".\\����\\user");
	char *user_id1 = (char *)malloc(sizeof(char) * 6);
	strcpy(user_id1, num2str(username));
	strcat(filename1, user_id1);
	strcat(filename1, "_name.txt");
	temp = fopen(filename1, "r");
	fscanf(temp, "%s", temp_name);
	fclose(temp);


	strcpy(filename2, ".\\����\\user");
	char *user_id2 = (char *)malloc(sizeof(char) * 6);
	strcpy(user_id2, num2str(username));
	strcat(filename2, user_id2);
	strcat(filename2, "_score.txt");
	temp = fopen(filename2, "r");
	fscanf(temp, "%d", &temp_score);
	fclose(temp);

	InitConsole();
	printf("��ǰ�û���Ϣ��\n");
	printf("�û���       ��ߵ÷�\n");
	printf("%s\t%d\n", temp_name, temp_score);
	printf("\n��رմ˴��ڡ�\n");
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