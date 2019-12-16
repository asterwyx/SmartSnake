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
	game->isOver = NO;
	game->hasWon = NO;
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
		game->isOver = YES;  // �ı���Ϸ״̬
	}
	// TODO ����Լ����Լ�����ײ
	if ((collidedPos = checkCollision(game->foods, game->snake)) != NULL)
	{
		// ����ߵĳ���
		addTail(game->snake);
		// �ӷ�
		game->score += FOOD_SCORE;
		// TODO ɾ�����Ե���ʳ��
	}
	if ((collidedPos = checkCollision(game->mines, game->snake)) != NULL)
	{
		// �����ߵĳ��ȵ�ԭ����һ��
		deleteHalf(game->snake);
		// ���ٷ�����ԭ����һ��
		game->score = game->score / 2;
		// TODO ɾ���������ĵ���

	}
	if ((collidedPos = checkCollision(game->poisonousWeeds, game->snake)) != NULL)
	{
		deleteOne(game->snake); // ���ȼ�һ
		game->score += POISON_SCORE; // �ı�÷�
		// TODO ɾ�����Ե��Ķ���


	}
	if ((collidedPos = checkCollision(game->wisdomGrass, game->snake)) != NULL)
	{
		game->snake->hasWisdom = YES; // ����ӵ���ǻ۲�״̬
		game->score += WISDOM_SCORE; // �ı����
		// TODO ɾ�����Ե����ǻ۲�

	}
}
