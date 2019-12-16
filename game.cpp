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
	return Game();
}

FILE* saveGame(Game game)
{

}