#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include <stdlib.h>
#include <sysinfoapi.h>
#include <easyx.h>
#include <string.h>

status initGame(Game game, Level level)
{
	if (game == NULL)
	{
		perror("NULL game");
		return ERROR;
	}
	game->score = 0; // 得分置零
	game->level = level; // 设置等级
	game->screening = 1; // 设置关卡
	game->snake = (Snake)malloc(sizeof(struct snake));
	game->foods = (PtrToObject)malloc(sizeof(Object));
	game->mines = (PtrToObject)malloc(sizeof(Object));
	game->poisonousWeeds = (PtrToObject)malloc(sizeof(Object));
	game->walls = (PtrToObject)malloc(sizeof(Object));
	game->wisdomGrass = (PtrToObject)malloc(sizeof(Object));
	game->isOver = NO;
	game->hasWon = NO;
	game->poisonTimer1 = YES;
	game->poisonTimer2 = GetTickCount();
	if (!initSnake(game->snake, STARTX, STARTY) &&
		!initObject(game->foods, FOOD) &&
		!initObject(game->mines, MINE) &&
		!initObject(game->poisonousWeeds, POISONOUSWEEDS) &&
		!initObject(game->walls, WALL) &&
		!initObject(game->wisdomGrass, WISDOMGRASS))
	{
		// 全部初始化完成返回0;
		return YES;
	}
	else
	{
		return NO;
	}
}

void nextScreening(Game game)
{
	cleardevice();
	outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "加载中");
	game->screening++; // 设置关卡
	game->isOver = NO;
	game->hasWon = NO; // 状态重置
	game->poisonTimer1 = YES;
	game->poisonTimer2 = GetTickCount(); // 重置计时器
	resetSnake(game->snake, DEFAULT_MOVE_SPEED + 3 * game->level);
	// 清除原有信息，复用链表
	clearObject(game->foods);
	clearObject(game->mines);
	clearObject(game->poisonousWeeds);
	clearObject(game->walls);
	clearObject(game->wisdomGrass);
	// 添加交互物体
	for (int i = 0; i < DEFAULT_FOOD_NUMBER - game->level; i++)
	{
		o_addObject(game->foods); // 初始化食物
	}
	for (int i = 0; i < DEFAULT_MINE_NUMBER + 2 * game->level; i++)
	{
		o_addObject(game->mines); // 初始化地雷
	}
	for (int i = 0; i < DEFAULT_POISON_NUMBER + 2 * game->level; i++)
	{
		o_addObject(game->poisonousWeeds); // 初始化毒草
	}
	for (int i = 0; i < DEFAULT_WALL_NUMBER + 3 * game->level + game->screening; i++)
	{
		o_addObject(game->walls); // 初始化墙
	}
	for (int i = 0; i < DEFAULT_WISDOM_NUMBER - game->level; i++)
	{
		o_addObject(game->wisdomGrass); // 初始化智慧草
	}
}

void newGame(Game game)
{
	cleardevice();
	outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "加载中");
	// 这个函数只在游戏已经初始化了之后调用，已经设置等级，等级不需要被更改
	// 从第一关开始
	game->screening = 1;
	game->score = 0; // 得分清零
	game->isOver = NO;
	game->hasWon = NO; // 状态重置
	game->poisonTimer1 = YES;
	game->poisonTimer2 = GetTickCount(); // 重置计时器
	resetSnake(game->snake, DEFAULT_MOVE_SPEED + 3 * game->level);
	// 清除原有信息，复用链表
	clearObject(game->foods);
	clearObject(game->mines);
	clearObject(game->poisonousWeeds);
	clearObject(game->walls);
	clearObject(game->wisdomGrass);
	// 添加交互物体
	for (int i = 0; i < DEFAULT_FOOD_NUMBER - game->level; i++)
	{
		o_addObject(game->foods); // 初始化食物
	}
	for (int i = 0; i < DEFAULT_MINE_NUMBER + 2 * game->level; i++)
	{
		o_addObject(game->mines); // 初始化地雷
	}
	for (int i = 0; i < DEFAULT_POISON_NUMBER + 2 * game->level; i++)
	{
		o_addObject(game->poisonousWeeds); // 初始化毒草
	}
	for (int i = 0; i < DEFAULT_WALL_NUMBER + 3 * game->level; i++)
	{
		o_addObject(game->walls); // 初始化墙
	}
	for (int i = 0; i < DEFAULT_WISDOM_NUMBER - game->level; i++)
	{
		o_addObject(game->wisdomGrass); // 初始化智慧草
	}
}

Game loadGame(FILE* fp)
{
	return NULL;
}

FILE* saveGame(Game game)
{
	return NULL;
}

void checkCollisions(Game game)
{
	PtrToNode collidedPos = NULL;
	// 检测边界碰撞
	if (game->snake->head->x <= 0 || game->snake->head->x >= MAP_WIDTH ||
		game->snake->head->y <= 0 || game->snake->head->y >= MAP_HEIGHT)
	{
		// 宽松边界检测，仅检测大幅度撞上
		game->isOver = YES;
	}
	if ((collidedPos = checkCollision(game->walls, game->snake)) != NULL)
	{
		game->isOver = YES;  // 改变游戏状态
	}
	// TODO 检测自己与自己的碰撞
	if ((collidedPos = checkCollision(game->foods, game->snake)) != NULL)
	{
		// 添加蛇的长度
		addTail(game->snake);
		// 加分
		game->score += FOOD_SCORE;
		// 删除被吃掉的食物
		o_deleteOne(collidedPos, game->foods);
		// 新增一个食物
		o_addObject(game->foods);
	}
	if ((collidedPos = checkCollision(game->mines, game->snake)) != NULL)
	{
		if (game->snake->length == 0)
		{
			game->isOver = YES;
		}
		else
		{
			// 减少蛇的长度到原来的一半
			deleteHalf(game->snake);
			// 减少分数到原来的一半
			game->score = game->score / 2;
			// 删除被碰掉的地雷
			o_deleteOne(collidedPos, game->mines);
			//新增一个地雷
			o_addObject(game->mines);
		}
	}
	if ((collidedPos = checkCollision(game->poisonousWeeds, game->snake)) != NULL)
	{
		if (game->snake->length == 1)
		{
			game->isOver = YES;
		}
		else
		{
			deleteOne(game->snake); // 长度减一
			game->score += POISON_SCORE; // 改变得分
			// 删除被吃掉的毒草
			o_deleteOne(collidedPos, game->poisonousWeeds);
		}		
	}
	if ((collidedPos = checkCollision(game->wisdomGrass, game->snake)) != NULL)
	{
		game->snake->hasWisdom = YES; // 设置拥有智慧草状态
		game->score += WISDOM_SCORE; // 改变分数
		// 删除被吃掉的智慧草
		o_deleteOne(collidedPos, game->wisdomGrass);
		o_addObject(game->wisdomGrass); // 新增一个智慧草
	}
	// 胜利检测
	if (game->snake->length >= WIN_LENGTH)
	{
		game->hasWon = YES;
	}
	if (game->isOver == YES)
	{
		int scores[10] = { 0 };
		freopen("scores.txt", "r", stdin);
		for (size_t i = 0; i < 10; i++)
		{
			scanf("%d", scores + i);
		}
		for (int i = 0; i < 10; i++)
		{
			if (game->score > scores[i])
			{
				for (int j = i + 1; j < 10; j++)
				{
					scores[j] = scores[j - 1];
				}
				scores[i] = game->score;
				break;
			}
		}
		fclose(stdin);
		freopen("scores.txt", "w", stdout);
		for (int i = 0; i < 10; i++)
		{
			printf("%d ", scores[i]);
		}
		fclose(stdout);
	}
}

void updateUI(Game game)
{
	setfillcolor(RGB(0, 255, 0));
	fillrectangle(0, 0, MAP_WIDTH, MAP_HEIGHT);
	// 包括定时检测和生成交互物体控制
	drawSnake(game->snake); // 画蛇
	drawObject(game->foods); // 画食物
	drawObject(game->mines); // 画地雷
	if ((GetTickCount() - game->poisonTimer2) > POISON_EXIST_TIME)
	{
		clearObject(game->poisonousWeeds); // 检测毒草是否应该消失
	}
	if (game->poisonTimer1 == YES)
	{
		drawObject(game->poisonousWeeds); // 闪烁画毒草
		game->poisonTimer1 = NO;
	}
	else
	{
		game->poisonTimer1 = YES;
	}
	drawObject(game->walls); // 画墙
	drawObject(game->wisdomGrass); // 画智慧草
	outtextxy(MAP_WIDTH + 50, 100, "当前分数");
	TCHAR buffer[100];
	sprintf_s(buffer, "%d", game->score);
	outtextxy(MAP_WIDTH + 50, 150, buffer);
	outtextxy(MAP_WIDTH + 100, 200, "当前长度");
	sprintf_s(buffer, "%d", game->snake->length);
	outtextxy(MAP_WIDTH + 50, 250, buffer);
	sprintf_s(buffer, "%d", game->screening);
	outtextxy(MAP_WIDTH + 50, 300, "当前关卡");
	outtextxy(MAP_WIDTH + 50, 350, buffer);
}