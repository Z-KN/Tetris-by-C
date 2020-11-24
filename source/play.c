#include "head.h"

extern int is_ui;
extern int to_play_game;

int x = Left_Up_x + (Right_Up_x - Left_Up_x) / 2 - 2;//掉下来之前的坐标
int y = Left_Up_y + 3;
int rotate = 0;//旋转次数
int now_block = 0;//现在的物块类型
int next_block = 0;//下一个物块类型
char col_num[10];//颜色数组
int is_stop = 0;//是否停下
double droptime = 0.3;//下落时间（难度）
double length;//方块边长
int username = 1;//当前用户名
int is_continue = 0;//是否继续
int score = 0;//得分

struct Board
{
	int data[Board_X][Board_Y];
	int color[Board_X][Board_Y];
}board;
struct Block
{
	int shape[4][4];
} block[7][4] = { 0 };

char *color(int color)
{
	switch (color)
	{
	case 0: strcpy(col_num, "Blue");
		break;
	case 1: strcpy(col_num, "Red");
		break;
	case 2: strcpy(col_num, "Orange");
		break;
	case 3: strcpy(col_num, "Yellow");
		break;
	case 4: strcpy(col_num, "Green");
		break;
	case 5: strcpy(col_num, "Violet");
		break;
	case 6: strcpy(col_num, "Gray");
		break;
	case 7: strcpy(col_num, "Black");
		break;
	case 8: strcpy(col_num, "Cyan");
		break;
	};

	return col_num;
}

void init_block_data(void)
{
	int i, j,k,m;
	int temp[4][4] = { 0 };
	//画7种block

	// ****
	for (i = 0; i < 4; i++)
		block[0][0].shape[2][i] = 1;

	//  *
	// ***
	block[1][0].shape[1][1] = 1;
	for (i = 0; i < 3; i++)
		block[1][0].shape[2][i] = 1;

	//  ** 
	// **
	for (i = 1; i < 3; i++)
		block[2][0].shape[1][i] = 1;
	for (i = 0; i < 2; i++)
		block[2][0].shape[2][i] = 1;
	
	// ** 
	//  **
	for (i = 0; i < 2; i++)
		block[3][0].shape[1][i] = 1;
	for (i = 1; i < 3; i++)
		block[3][0].shape[2][i] = 1;

	//   *
	// ***
	block[4][0].shape[1][2] = 1;
	for (i = 0; i < 3; i++)
		block[4][0].shape[2][i] = 1;

	// *
	// ***
	block[5][0].shape[1][1] = 1;
	for (i = 1; i < 4; i++)
		block[5][0].shape[2][i] = 1;

	// **
	// **
	for (i = 1; i < 3; i++)
		block[6][0].shape[1][i] = 1; 
	for (i = 1; i < 3; i++)
		block[6][0].shape[2][i] = 1;


	//四重循环来依次翻转
	for(i=0;i<7;i++)
	{
		for(m=0;m<3;m++)
		{
			for(j=0;j<4;j++)
			{
				for(k=0;k<4;k++)
				{
					temp[j][k]=block[i][m].shape[j][k];
				}
			}
			for(j=0;j<4;j++)
			{
				for(k=0;k<4;k++)
				{
					block[i][m+1].shape[j][k]=temp[4-k-1][j];
				}
			}
		}
	}
}
void drawblock(int shape_type, int rotate, int x, int y, char *color)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[shape_type][rotate].shape[i][j] == 1&&y-i<=Right_Up_y)
			{
				SetPenColor(color);
				drawBox((x+j)*length, (y-i)*length, 0.90*length, 0.90*length, 1, " ", ' ', color);
			}
		}
	}
}
void coverblock(int shape_type, int rotate, int x, int y, char *color)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[shape_type][rotate].shape[i][j] == 1&&y-i<=Right_Up_y)
			{
				SetPenColor(color);
				drawBox((x+j)*length, (y-i)*length, length, length, 1, " ", ' ', color);
			}
		}
	}
}

int check_bottom(int shape_type, int rotate, int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[shape_type][rotate].shape[i][j] == 0)
				continue;
			if ((board.data[x+j][y-i] == side )||( board.data[x+j][y-i] == FILLED))
				return 0;
		}
	}
	return 1;
}
void check_clear_line(void)
{
	int i, j, sum = 0, count = 0,line_index = 0;
	for (i = Left_Down_y; i < Left_Up_y; i++)
	{
		sum = 0;
		for (j = Left_Down_x; j <= Right_Down_x; j++)
			sum += board.data[j][i];
		if (sum == 0)
			break;
		if (sum == Right_Down_x - Left_Down_x+1)
		{
			count++;
			if (count == 1)
				line_index = i;
		}
	}
	if (count > 0)
	{
		clear_line(line_index, count);
		add_score(count);
	}
}
void clear_line(int line_index,int count)
{
	int i, j;
	for (i = line_index; i <= Left_Up_y-count; i++)
	{
		for (j = Left_Down_x; j <= Right_Down_x; j++)
		{
			board.data[j][i] = board.data[j][i+count];
			board.color[j][i] = board.color[j][i+count];
		}
	}
	for (j = 0; j < count; j++)
	{
		for (i = Left_Up_x; i <= Right_Up_x; i++)
		{
			board.data[i][Right_Up_y-j] = EMPTY;
			board.color[i][Right_Up_y-j] = Board_color;
		}
	}
	
	draw_gameface();
}

void add_score(int count)
{
	int addscore = 0;
	int i;
	int score_num = 0;
	int temp = 0;

	switch (count)
	{
	case 1: addscore = 100; break;
	case 2: addscore = 200; break;
	case 3: addscore = 400; break;
	case 4: addscore = 800; break;
	}
	score += addscore;
	SetPenSize(1);
	SetPenColor("White");
	drawBox((Right_Up_x + 7)*length, (Right_Up_y - 4)*length, 6 * length, 1 * length, 1, " ", 'L', "White");
	SetPenColor("Black");

	MovePen((Right_Up_x + 3.5)*length, (Right_Up_y -9 )*length);
	SetPenSize(1);

	MovePen((Right_Up_x + 8)*length, (Right_Up_y -4)*length);
	temp = score;
	do
	{
		score_num++;
		temp /= 10;
	} while (temp != 0);

	char *score_arr = malloc(score_num * (sizeof(char)+1));
	temp = score;
	for (i = 0; i < score_num; i++)
	{
		*(score_arr + score_num - i-1) = '0' + temp % 10;
		temp /= 10;
	}
	*(score_arr + score_num) = 0;
	DrawTextString(score_arr);
	free(score_arr);
	SetPenSize(1);
}
char *num2str(int num)
{

	int a[5];
	int i = 0;
	int j = 0;
	int k = 0;
	char string[6];
	do
	{
		a[i] = num % 10;
		num /= 10;
		i++;
	} while (num);
	for (j=1,k=0;j<=i;j++,k++)
	{
		string[k] = a[i-j]+'0';
	}
	string[k] = 0;
	return string;
}

int check_gameover(void)
{
	int i;
	for (i = Left_Up_x; i <= Right_Up_x; i++)
		if (board.data[i][Left_Up_y] == FILLED)
			return 1;
	return 0;
}
void gameover(void)
{
	int i, j;
	FILE *userdata_score;
	int old_score = 0;
	stop();
	char filename[30];
	strcpy(filename, ".\\数据\\user");
	char *user_id = num2str(username);
	strcat(filename, user_id);
	strcat(filename, "_score.txt");
	userdata_score = fopen(filename, "r");
	if (userdata_score == NULL)
	{
		userdata_score = fopen(filename, "w");
		fprintf(userdata_score, "%d ", score);
	}
	else
	{
		userdata_score = fopen(filename, "r+");
		fscanf(userdata_score, "%d ", &old_score);
		if (old_score < score)
		{
			rewind(userdata_score);
			fprintf(userdata_score, "%d ", score);
		}
	}
	if (fclose(userdata_score) != 0)
	{
		exit(EXIT_FAILURE);
	}
	MovePen(((Left_Up_x + Right_Up_x) / 2 - 2)*length, Slength-3*length);
	SetPenColor("Red");
	SetPenSize(15);
	DrawTextString("GAME OVER!");
	Pause(1);
	to_play_game = 0;
	is_stop = 1;
	is_ui = 1;
}

void init_gameface(void)
{
	int i, j;
	if (is_continue == 0)
	{
		for (j = Left_Down_y; j <= Left_Up_y; j++)
			for (i = Left_Down_x; i <= Right_Down_x; i++)
			{
				board.data[i][j] = EMPTY;
				board.color[i][j] = Board_color;
			}
	}
	else
	{
		FILE *file;
		char filename[30];
		strcpy(filename, ".\\数据\\user");
		char *user_id = num2str(username);
		strcat(filename, user_id);
		strcat(filename, "_game.txt");
		file = fopen(filename, "r");
		if (file == NULL)
		{
			exit(EXIT_FAILURE);
		}
		for (j = Left_Down_y; j <= Left_Up_y; j++)
			for (i = Left_Down_x; i <= Right_Down_x; i++)
			{
				fscanf(file, " %d %d", &board.data[i][j],&board.color[i][j]);	
			}
		fscanf(file, " %d %d %d %lf %d %d %d", &x, &y, &rotate, &droptime, &now_block, &next_block, &score);
		if (fclose(file) != 0)
		{
			exit(EXIT_FAILURE);
		}
		is_continue = 0;
	}
} 
void draw_interface(void)
{
	int i;
	for (i = Left_Down_y - 1; i <= Left_Up_y + 1; i++)
	{
		board.data[Left_Down_x-1][i] = side;
		SetPenColor(color(sidecolor));
		drawBox((Left_Down_x - 1)*length, i*length, length, length, 1, " ", ' ', "");
	}
	for (i = Left_Up_x; i <= Right_Up_x + 1; i++)
	{
		board.data[i][Left_Up_y+1] = EMPTY;
		SetPenColor(color(sidecolor));
		drawBox(i*length, (Left_Up_y + 1)*length, length, length, 1, " ", ' ', "");

	}
	for (i = Right_Up_y; i >= Right_Down_y - 1; i--)
	{
		board.data[Right_Up_x + 1][i] = side;
		SetPenColor(color(sidecolor));
		drawBox((Right_Up_x + 1)*length, i*length, length, length, 1, " ", ' ', "");
	}
	for (i = Right_Down_x; i >= Left_Down_x; i--)
	{
		board.data[i][Right_Down_y - 1] = side;
		SetPenColor(color(sidecolor));
		drawBox(i*length, (Right_Down_y - 1)*length, length, length, 1, " ", ' ', "");
	}

	SetPenColor("Black");
	SetPenSize(2);
	MovePen((Right_Up_x+3)*length, 0);
	DrawLine(0, Slength);
	
	drawLabel((Right_Up_x + 4)*length, (Right_Up_y + 4)*length, "下一个图形：");
	
	MovePen((Right_Up_x + 3)*length, (Right_Up_y -2.5)*length);
	DrawLine(Slength-(Right_Up_x + 3)*length,0 );

	drawLabel((Right_Up_x + 5)*length, (Right_Up_y -4)*length, "分数：");

	
	add_score(0);
	
	draw_tool();
}
void draw_gameface(void)
{
	int i, j;
	for (j = Left_Down_y; j <= Left_Up_y; j++)
	{
		for (i = Left_Down_x; i <= Right_Down_x; i++)
		{
			SetPenColor(color(Board_color));
			drawBox(i*length, j*length, length, length, 1, " ", ' ', "Black");
		}
	}
	for (j = Left_Down_y; j <= Left_Up_y; j++)
	{
		for (i = Left_Down_x; i <= Right_Down_x; i++)
		{
			SetPenColor(color(board.color[i][j]));
			drawBox(i*length, j*length, 0.9*length, 0.9*length, 1, " ", ' ', "Black");
		}
	}
}
void draw_tool(void)
{
	SetPenSize(3);
	drawBox((Right_Up_x + 3.6)*length, (Right_Up_y - 7)*length, 3.5*length, 2*length, 0, "暂停|P", ' ', "Red");

	SetPenColor("Black");
	drawBox((Right_Up_x + 8.1)*length, (Right_Up_y - 7)*length, 3.5*length,2* length, 0, "开始|S", ' ', "Red");
	SetPenColor("Black");
	drawBox((Right_Up_x + 3.6)*length, (Right_Up_y - 10)*length, 3.5*length,2* length, 0, "重玩|R", ' ', "Red");
	SetPenColor("Black");
	drawBox((Right_Up_x + 8.1)*length, (Right_Up_y - 10)*length, 3.5*length,2* length, 0, "结束|E", ' ', "Red");
	SetPenColor("Black");
	drawBox((Right_Up_x + 5.85)*length, (Right_Up_y - 13)*length, 3.5*length,2* length, 0, "返回", ' ', "Red");

	drawLabel((Right_Up_x + 3.6)*length, (Right_Up_y - 15)*length, "难度：");
	if (droptime == 0.1) 
	{
		drawBox((Right_Up_x + 7)*length, (Right_Up_y - 15.25)*length, 3.5 * length, 1 * length, 1, " ", 'L', "White");
		drawLabel((Right_Up_x + 8.2)*length, (Right_Up_y - 15)*length, "困难");
	}
		else if(droptime==0.2)
	{
		drawBox((Right_Up_x + 7)*length, (Right_Up_y - 15.25)*length, 3.5 * length, 1 * length, 1, " ", 'L', "White");
		drawLabel((Right_Up_x + 8.2)*length, (Right_Up_y - 15)*length, "中等");
	}
		else
	{
		drawBox((Right_Up_x + 7)*length, (Right_Up_y - 15.25)*length, 3.5 * length, 1 * length, 1, " ", 'L', "White");
		drawLabel((Right_Up_x + 8.2)*length, (Right_Up_y - 15)*length, "简单");
	}
	SetPenColor("Black");
	drawLabel((Right_Up_x + 3.6)*length, (Right_Up_y - 16.5)*length, "难度选择：");
		
	drawBox((Right_Up_x + 7)*length, (Right_Up_y - 16.75)*length, 3.5*length, 1.1 * length, 0, "简单", ' ', "Red");
	SetPenColor("Black");
	drawBox((Right_Up_x + 7)*length, (Right_Up_y - 18.1)*length, 3.5*length, 1.1 * length, 0, "中等", ' ', "Red");
	SetPenColor("Black");
	drawBox((Right_Up_x + 7)*length, (Right_Up_y - 19.45)*length, 3.5*length, 1.1 * length, 0, "困难", ' ', "Red");
	SetPenColor("Black");
	SetPenSize(1);
}
 
void keyboard_event_process(int key, int event)
{
	switch (event)
	{
	case KEY_DOWN:
		switch (key)
		{

		case VK_LEFT:
			if (check_bottom(now_block, rotate, x - 1, y) && (!is_stop))
			{
				coverblock(now_block, rotate, x, y, color(Board_color));
				x--;
				drawblock(now_block, rotate, x, y, color(now_block));
			}
			break;

		case VK_RIGHT:
			if (check_bottom(now_block, rotate, x + 1, y) && (!is_stop))
			{
				coverblock(now_block, rotate, x, y, color(Board_color));
				x++;
				drawblock(now_block, rotate, x, y, color(now_block));
			}
			break;
		case VK_DOWN:
			if (check_bottom(now_block, rotate, x, y - 1) && check_bottom(now_block, rotate, x, y - 2) && (!is_stop))
			{
				coverblock(now_block, rotate, x, y, color(Board_color));
				y--;
				drawblock(now_block, rotate, x, y, color(now_block));
			}
			break;

		case VK_UP:
			if (check_bottom(now_block, (rotate + 1) % 4, x, y) && (!is_stop))
			{
				coverblock(now_block, rotate, x, y, color(Board_color));
				rotate = (rotate + 1) % 4;
				drawblock(now_block, rotate, x, y, color(now_block));
			}
			break;
		case 'P':
		case 'p':
			if (is_stop == 0)
				stop();
			else if (is_stop == 1)
				start();
			break;
		case 'R':
		case 'r':
			restart();
			break;
		case 'E':
		case 'e':
			end();
		case 'S':
		case 's':
			start();
			break;
		}
	}
}
void mouse_event_process(int mouse_x, int mouse_y, int mouse_button, int mouse_event)
{
	uiGetMouse(mouse_x, mouse_y, mouse_button, mouse_event);
	double now_mouse_x = GetMouseX();
	double now_mouse_y = GetMouseY();
	double now_x = GetMouseX(), now_y = GetMouseY();
	switch (mouse_button)
	{
	case LEFT_BUTTON:
		switch (mouse_event)
		{
		case BUTTON_DOWN:
			now_x = ScaleXInches(mouse_x);
			now_y = ScaleYInches(mouse_y);
			if (now_x >= (Right_Up_x + 3.6)*length&& now_x <= (Right_Up_x + 7.1)*length && now_y >= (Right_Up_y - 7)*length  && now_y <= (Right_Up_y - 5)*length)
			{
				if (is_stop == 0)
					stop();
				else if (is_stop == 1)
					start();
				break;
			}
			if (now_x >= (Right_Up_x + 8.1)*length&&now_x <= (Right_Up_x + 11.6)*length&&now_y >= (Right_Up_y - 7)*length && now_y <= (Right_Up_y - 5)*length)
			{
				start();
				break;
			}
			if (now_x >= (Right_Up_x + 3.6)*length&&now_x <= (Right_Up_x + 7.1)*length&&now_y >= (Right_Up_y - 10)*length && now_y <= (Right_Up_y - 8)*length)
			{
				restart();
				break;
			}
			if (now_x >= (Right_Up_x + 8.1)*length&&now_x <= (Right_Up_x + 11.6)*length&&now_y >= (Right_Up_y - 10)*length&&now_y <= (Right_Up_y - 8)*length)
			{
				end();
				break;
			}
			if (now_x >= (Right_Up_x + 5.85)*length&&now_x <= (Right_Up_x + 9.35)*length&&now_y >= (Right_Up_y - 13)*length&&now_y <= (Right_Up_y - 11)*length)
			{
				back();
				break;
			}
			if (now_x >= (Right_Up_x + 7)*length&&now_x <= (Right_Up_x + 10.5)*length&&now_y >= (Right_Up_y - 16.75)*length&&now_y <= (Right_Up_y - 15.65)*length)
			{
				droptime = 0.3;
				draw_tool();
				start();
				break;
			}
			if (now_x >= (Right_Up_x + 7)*length&&now_x <= (Right_Up_x + 10.5)*length&&now_y >= (Right_Up_y - 18.1)*length&&now_y <= (Right_Up_y - 17)*length)
			{
				droptime = 0.2;
				draw_tool();
				start();
				break;
			}
			if (now_x >= (Right_Up_x + 7)*length&&now_x <= (Right_Up_x + 10.5)*length&&now_y >= (Right_Up_y - 19.45)*length&&now_y <= (Right_Up_y - 18.35)*length)
			{
				droptime = 0.1;
				draw_tool();
				start();
				break;
			}

		}
	}
}

void game(void)
{
	InitGraphics();
	SetWindowSize(Slength, Slength);
	SetWindowTitle("俄罗斯方块");
	length = Slength / 30;

	registerKeyboardEvent(keyboard_event_process);
	registerMouseEvent(mouse_event_process);
	x = Left_Up_x + (Right_Up_x - Left_Up_x) / 2 - 2;
	y = Left_Up_y + 3;

	srand(time(NULL));
	//InitConsole();
	score = 0;
	now_block = rand() % 7;
	next_block = rand() % 7;
	init_gameface();
	draw_interface();
	init_block_data();
	SetPenSize(1);
	draw_gameface();

	Pause(1);
	while (!is_stop)
	{
		registerKeyboardEvent(keyboard_event_process);
		play_game();
	}
}
void play_game()
{
	registerKeyboardEvent(keyboard_event_process);
	registerMouseEvent(mouse_event_process);
	int i, m, n;
	drawblock(next_block, 0, Right_Up_x + 6, Right_Up_y+1, color(next_block));
	while(1)
	{
		Pause(droptime);
		if(check_bottom(now_block,rotate,x,y-1))
		{
			if (is_stop!=1)
			{
				coverblock(now_block, rotate, x, y, color(Board_color));
				y--;
				drawblock(now_block, rotate, x, y, color(now_block));
			}
		}
		else 
		{
			for(m=0;m<4;m++)
			{
				for(n=0;n<4;n++)
				{
					if(block[now_block][rotate].shape[m][n] == 1) 
					{
						board.data[x+n][y-m] = FILLED;
						board.color[x + n][y - m] = now_block;
					}
				}
			}
			break;
		}
	}

	if (check_gameover()) gameover();
	check_clear_line();
	now_block = next_block;
	coverblock(next_block, 0, Right_Up_x + 6, Right_Up_y +1, "White");
	next_block = rand() % 7;
	x = Left_Up_x + (Right_Up_x - Left_Up_x) / 2 - 2;
	y = Left_Up_y + 3;
	rotate = 0;
}

void stop(void)
{
		is_stop = 1;
}
void start(void)
{
		is_stop = 0;
}
void restart(void)
{
	game();
}
void end(void)
{
	stop();
	FILE *userdata_game;
	int i, j;
	char filename[30];
	strcpy(filename, ".\\数据\\user");
	char *user_id = num2str(username);
	strcat(filename, user_id);
	strcat(filename, "_game.txt");
	userdata_game = fopen(filename, "w");
	if (userdata_game == NULL)
	{
		exit(EXIT_FAILURE);
	}
	for(j=Left_Down_y;j<=Left_Up_y;j++)
		for (i = Left_Down_x; i <= Right_Down_x; i++)
		{
			fprintf(userdata_game, " %d %d", board.data[i][j],board.color[i][j]);
		}
	fprintf(userdata_game, " %d %d %d %f %d %d %d", x, y, rotate, droptime, now_block,next_block ,score);
	if (fclose(userdata_game) != 0)
	{
		exit(EXIT_FAILURE);
	}
	InitGraphics();
	main_ui();
}
void back(void)
{
	gameover();
	Main();
}