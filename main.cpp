#define _CRT_SECURE_NO_WARNINGS
#include "define.h"
#include <easyx.h>
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "snake.h"
#include <sysinfoapi.h>
#include "game.h"
#define FONT_SIZE 16
#define FONT_DIST 30


void initGraph();
int getKey();
int enterStartScene();
Level selectLevel();

int main()
{
	initGraph(); // 图形显示方式初始化
	int selection = enterStartScene();
	Game game = (Game)malloc(sizeof(struct game));
	Level gameLevel = EASY;
	switch (selection)
	{
	case STARTNEW:
		gameLevel = selectLevel();
		initGame(game, gameLevel);
		newGame(game); // 开局
		break;
	case LOADGAME:
		free(game);
		game = loadGame(NULL);
		break;
	case EXIT:
		closegraph();
		return 0;
	default:
		break;
	}
	int currentCount = 0;
	while (1)
	{
		do
		{
			do
			{
				if ((GetTickCount() - currentCount) > DELTA)
				{
					moveSnake(game->snake);
					checkCollisions(game);
					cleardevice();
					updateUI(game);
					currentCount = GetTickCount();
				}

				while (MouseHit())
				{
					MOUSEMSG mouseMsg = GetMouseMsg();
					if (mouseMsg.mkLButton)
					{
						game->snake->xDirection = (mouseMsg.x - game->snake->head->x) / dist(game->snake->head->x, game->snake->head->y, mouseMsg.x, mouseMsg.y);
						game->snake->yDirection = (mouseMsg.y - game->snake->head->y) / dist(game->snake->head->x, game->snake->head->y, mouseMsg.x, mouseMsg.y);
					}

				}
			} while (game->isOver == NO && game->hasWon == NO);
			if (game->hasWon == YES)
			{
				cleardevice();
				outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "你赢了");
				outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + FONT_DIST, "按'Y'开始下一关");
				int val = _getch();
				if (val == 'Y')
				{
					nextScreening(game);
					continue;
				}
				else
				{
					break;
				}
			}
		} while (game->isOver == NO);
		cleardevice();
		int scores[10] = { 0 };
		freopen("scores.txt", "r", stdin);
		for (size_t i = 0; i < 10; i++)
		{
			scanf("%d", scores + i);
		}
		fclose(stdin);
		char buffer[20];
		for (int i = 0; i < 10; i++)
		{
			sprintf_s(buffer, "%d      %d", i + 1, scores[i]);
			outtextxy(WINDOW_WIDTH / 2, 100 + i * FONT_DIST, buffer);
		}
		outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 200, "你输了");
		outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + FONT_DIST + 200, "按'Y'开始新游戏");
		int val = _getch();
		if (val == 'Y')
		{
			newGame(game);
			continue;
		}
		else
		{
			break;
		}
	}
	closegraph();
	return 0;
}

void initGraph()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);   // 创建绘图窗口，大小为 640x480 像素
}

double dist(int x1, int y1, int x2, int y2)
{
	double distance;
	distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return distance;
}

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

int enterStartScene()
{
	cleardevice();
	outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - FONT_DIST, "开始游戏");
	outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "加载进度");
	outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + FONT_DIST, "退出游戏");
	while (1)
	{
		MOUSEMSG mouseMsg = GetMouseMsg();
		if (mouseMsg.mkLButton)
		{
			if (mouseMsg.x > WINDOW_WIDTH / 2 - 2 * FONT_SIZE && mouseMsg.x < WINDOW_WIDTH / 2 + 2 * FONT_SIZE)
			{
				if (mouseMsg.y > WINDOW_HEIGHT / 2 - 1.5 * FONT_DIST && mouseMsg.y < WINDOW_HEIGHT / 2 - 0.5 * FONT_DIST)
				{
					return STARTNEW; // 开始游戏
				}
				else if (mouseMsg.y > WINDOW_HEIGHT / 2 - 0.5 * FONT_DIST && mouseMsg.y < WINDOW_HEIGHT / 2 + 0.5 * FONT_DIST)
				{
					return LOADGAME; // 加载进度
				}
				else if (mouseMsg.y > WINDOW_HEIGHT / 2 + 0.5 * FONT_DIST && mouseMsg.y < WINDOW_HEIGHT / 2 + 1.5 * FONT_DIST)
				{
					return EXIT; // 退出游戏
				}
			}
		}
	}
}

Level selectLevel()
{
	cleardevice();
	outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - FONT_DIST, "简单");
	outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "一般");
	outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + FONT_DIST, "困难");
	while (1)
	{
		MOUSEMSG mouseMsg = GetMouseMsg();
		if (mouseMsg.mkLButton)
		{
			if (mouseMsg.x > WINDOW_WIDTH / 2 - FONT_SIZE && mouseMsg.x < WINDOW_WIDTH / 2 + FONT_SIZE)
			{
				if (mouseMsg.y > WINDOW_HEIGHT / 2 - 1.5 * FONT_DIST && mouseMsg.y < WINDOW_HEIGHT / 2 - 0.5 * FONT_DIST)
				{
					return EASY; // 简单
				}
				else if (mouseMsg.y > WINDOW_HEIGHT / 2 - 0.5 * FONT_DIST && mouseMsg.y < WINDOW_HEIGHT / 2 + 0.5 * FONT_DIST)
				{
					return MEDIUM; // 一般
				}
				else if (mouseMsg.y > WINDOW_HEIGHT / 2 + 0.5 * FONT_DIST && mouseMsg.y < WINDOW_HEIGHT / 2 + 1.5 * FONT_DIST)
				{
					return HARD; // 困难
				}
			}
		}
	}
}
