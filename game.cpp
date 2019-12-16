#include "game.h"
#include <stdlib.h>

status initGame(Game game, Level level)
{
	if (game == NULL)
	{
		perror("NULL game");
		return ERROR;
	}
	game->score = 0; // �÷�����
	game->level = level; // ���õȼ�
	game->screening = 1; // ���ùؿ�
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
		// ȫ����ʼ����ɷ���0;
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