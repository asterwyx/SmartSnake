#include "define.h"
#include <easyx.h>
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "snake.h"
#include <sysinfoapi.h>


void initGraph();
void newGame();
int getKey();
//MOUSEMSG* getMouseMsg();
int checkWin();
int confirm(int status);
//int x = 200;
//int y = 200;
//double xDirection = 0;
//double yDirection = 0;


int main()
{
	initGraph(); // 图形显示方式初始化
	int gameRes = 0;
	int currentCount = 0;
	int addCount = 0;
	Snake snake = (Snake)malloc(sizeof(struct snake));
	if (snake == NULL)
	{
		perror("无法分配蛇结点！");
		exit(EXIT_FAILURE);
	}
	initSnake(snake, INIT_SNAKE_X, INIT_SNAKE_Y);
	MOUSEMSG* mouse = NULL;
	do
	{
		newGame(); // 开局
		do
		{
			if ((GetTickCount() - currentCount) > DELTA)
			{
				if ((GetTickCount() - addCount) > 10 * DELTA)
				{
					addTail(snake);
					addCount = GetTickCount();
				}
				//x += (int)SNAKE_MOVE_SPEED * xDirection;
				//y += (int)SNAKE_MOVE_SPEED * yDirection;
				moveSnake(snake);
				cleardevice();
				//circle(0, 0, 100);
				rectangle(0, 0, 100, 100);
				drawSnake(snake);
				currentCount = GetTickCount();
			}

			//mouse = getMouseMsg();
			int key = getKey(); // 读入操作信息
			
			if (key == ESC)
			{
				gameRes = 0; 
				break;
			}

			/*
			while (MouseHit())
			{
				mouse = getMouseMsg();
				if (mouse->mkLButton)
				{
					xDirection = (mouse->x - x) / dist(x, y, mouse->x, mouse->y);
					yDirection = (mouse->y - y) / dist(x, y, mouse->x, mouse->y);
				}
			}
			*/
			
			while (MouseHit())
			{
				MOUSEMSG mouseMsg = GetMouseMsg();
				//snake->xDirection = (mouseMsg.x - x) / dist(x, y, mouseMsg.x, mouseMsg.y);
				//snake->yDirection = (mouseMsg.y - y) / dist(x, y, mouseMsg.x, mouseMsg.y);
				
				if (mouseMsg.mkLButton)
				{
					snake->xDirection = (mouseMsg.x - snake->head->x) / dist(snake->head->x, snake->head->y, mouseMsg.x, mouseMsg.y);
					snake->yDirection = (mouseMsg.y - snake->head->y) / dist(snake->head->x, snake->head->y, mouseMsg.x, mouseMsg.y);
				}
				
			}
			
			
			/*
			// 按键事件判断响应
			switch(key)
			{
			case KEY_W:
				y -= 2;
				break;
			case KEY_S:
				y += 2;
				break;
			case KEY_A:
				x -= 2;
				break;
			case KEY_D:
				x += 2;
				break;
			default:
				break;
			}
			*/
			if (checkWin()) // 判断游戏是否胜利
				gameRes = 1;
		} while (!gameRes);
	} while (!confirm(gameRes));
	
	closegraph();
	return 0;
}

void initGraph()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);   // 创建绘图窗口，大小为 640x480 像素
	
}
/*
void s_detectgraph() {// 自定义图形检测
	int gdriver, gmode, errorcode;
	gdriver = VGA;
	gmode = VGAHI;
	registerbgidriver(EGAVGA_driver);
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != 0) {
		printf("\n\t\t\tGame : Snake Game\n");
		printf("\n\terror:\t%s\n", grapherrormsg(errorcode));
		getch();
		exit(1);
	}
}
*/

double dist(int x1, int y1, int x2, int y2)
{
	double distance;
	distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return distance;
}

void newGame()
{
	//circle(x, y, 100); // 画圆，圆心(200, 200)，半径 100
}

// 封装的获得鼠标事件指针的函数
/*
MOUSEMSG* getMouseMsg()
{
	if (MouseHit())
	{
		MOUSEMSG message = GetMouseMsg();
		return &message;
	}
	else
	{
		return NULL;
	}
}
*/

// 封装的获取键盘事件的函数
int getKey()
{
	if (_kbhit())
	{
		int val = _getch();
		return val;
	}
	else
	{
		return 0;
	}
}

int checkWin()
{
	return 0;
}



int confirm(int status)
{
	return status;
}