#include "define.h"
#include <easyx.h>
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#define DELTA 16
#define WIN 1
#define LOSE -1
#define CONTINUE 0
#define KEY_W 'W'


void initGraph();
void newGame();
int getKey();
int checkWin();
int confirm(int status);
int x = 200;
int y = 200;


int main()
{
	initGraph(); // 图形显示方式初始化
	int gameRes = 0;
	int currentCount = 0;
	do
	{
		newGame(); // 开局
		do
		{
			if ((GetTickCount() - currentCount) > DELTA)
			{
				cleardevice();
				circle(x, y, 100);
				currentCount = GetTickCount();
			}
			int key = getKey(); // 读入操作信息
			if (key == ESC)
			{
				gameRes = 0; 
				break;
			}
			
			switch(key)
			{
			case UP:
				y += 20;
				break;
			}
			
			if (checkWin()) // 判断游戏是否胜利
				gameRes = 1;
		} while (!gameRes);
	} while (!confirm(gameRes));
	
	closegraph();
	return 0;
}

void initGraph()
{
	initgraph(640, 480);   // 创建绘图窗口，大小为 640x480 像素
	
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

void newGame()
{
	circle(x, y, 100); // 画圆，圆心(200, 200)，半径 100
}

int getKey()
{
	if (!_kbhit())
	{
		int val = _getch();
		return val;
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