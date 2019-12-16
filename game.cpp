#include "game.h"
#include <stdlib.h>

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
	
}

void newGame(Game game)
{
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
		// TODO 删除被吃掉的食物
	}
	if ((collidedPos = checkCollision(game->mines, game->snake)) != NULL)
	{
		// 减少蛇的长度到原来的一半
		deleteHalf(game->snake);
		// 减少分数到原来的一半
		game->score = game->score / 2;
		// TODO 删除被碰掉的地雷

	}
	if ((collidedPos = checkCollision(game->poisonousWeeds, game->snake)) != NULL)
	{
		deleteOne(game->snake); // 长度减一
		game->score += POISON_SCORE; // 改变得分
		// TODO 删除被吃掉的毒草


	}
	if ((collidedPos = checkCollision(game->wisdomGrass, game->snake)) != NULL)
	{
		game->snake->hasWisdom = YES; // 设置拥有智慧草状态
		game->score += WISDOM_SCORE; // 改变分数
		// TODO 删除被吃掉的智慧草

	}
}
