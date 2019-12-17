#include "game.h"
#include <stdlib.h>
#include <sysinfoapi.h>

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
	game->poisonTimer1 = YES;
	game->poisonTimer2 = GetTickCount();
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
	game->screening++; // ���ùؿ�
	game->isOver = NO;
	game->hasWon = NO; // ״̬����
	game->poisonTimer1 = YES;
	game->poisonTimer2 = GetTickCount(); // ���ü�ʱ��
	resetSnake(game->snake, DEFAULT_MOVE_SPEED + 3 * game->level);
	// ���ԭ����Ϣ����������
	clearObject(game->foods);
	clearObject(game->mines);
	clearObject(game->poisonousWeeds);
	clearObject(game->walls);
	clearObject(game->wisdomGrass);
	// ��ӽ�������
	for (int i = 0; i < DEFAULT_FOOD_NUMBER - game->level; i++)
	{
		o_addObject(game->foods); // ��ʼ��ʳ��
	}
	for (int i = 0; i < DEFAULT_MINE_NUMBER + 2 * game->level; i++)
	{
		o_addObject(game->mines); // ��ʼ������
	}
	for (int i = 0; i < DEFAULT_POISON_NUMBER + 2 * game->level; i++)
	{
		o_addObject(game->poisonousWeeds); // ��ʼ������
	}
	for (int i = 0; i < DEFAULT_WALL_NUMBER + 3 * game->level + game->screening; i++)
	{
		o_addObject(game->walls); // ��ʼ��ǽ
	}
	for (int i = 0; i < DEFAULT_WISDOM_NUMBER - game->level; i++)
	{
		o_addObject(game->wisdomGrass); // ��ʼ���ǻ۲�
	}
}

void newGame(Game game)
{
	// �������ֻ����Ϸ�Ѿ���ʼ����֮����ã��Ѿ����õȼ����ȼ�����Ҫ������
	// �ӵ�һ�ؿ�ʼ
	game->screening = 1;
	game->score = 0; // �÷�����
	game->isOver = NO;
	game->hasWon = NO; // ״̬����
	game->poisonTimer1 = YES;
	game->poisonTimer2 = GetTickCount(); // ���ü�ʱ��
	resetSnake(game->snake, DEFAULT_MOVE_SPEED + 3 * game->level);
	// ���ԭ����Ϣ����������
	clearObject(game->foods);
	clearObject(game->mines);
	clearObject(game->poisonousWeeds);
	clearObject(game->walls);
	clearObject(game->wisdomGrass);
	// ��ӽ�������
	for (int i = 0; i < DEFAULT_FOOD_NUMBER - game->level; i++)
	{
		o_addObject(game->foods); // ��ʼ��ʳ��
	}
	for (int i = 0; i < DEFAULT_MINE_NUMBER + 2 * game->level; i++)
	{
		o_addObject(game->mines); // ��ʼ������
	}
	for (int i = 0; i < DEFAULT_POISON_NUMBER + 2 * game->level; i++)
	{
		o_addObject(game->poisonousWeeds); // ��ʼ������
	}
	for (int i = 0; i < DEFAULT_WALL_NUMBER + 3 * game->level; i++)
	{
		o_addObject(game->walls); // ��ʼ��ǽ
	}
	for (int i = 0; i < DEFAULT_WISDOM_NUMBER - game->level; i++)
	{
		o_addObject(game->wisdomGrass); // ��ʼ���ǻ۲�
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
	// ���߽���ײ
	if (game->snake->head->x <= 0 || game->snake->head->x >= MAP_WIDTH ||
		game->snake->head->y <= 0 || game->snake->head->y >= MAP_HEIGHT)
	{
		// ���ɱ߽��⣬���������ײ��
		game->isOver = YES;
	}
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
		// ɾ�����Ե���ʳ��
		o_deleteOne(collidedPos, game->foods);
		// ����һ��ʳ��
		o_addObject(game->foods);
	}
	if ((collidedPos = checkCollision(game->mines, game->snake)) != NULL)
	{
		// �����ߵĳ��ȵ�ԭ����һ��
		deleteHalf(game->snake);
		// ���ٷ�����ԭ����һ��
		game->score = game->score / 2;
		// ɾ���������ĵ���
		o_deleteOne(collidedPos, game->mines);
		//����һ������
		o_addObject(game->mines);
	}
	if ((collidedPos = checkCollision(game->poisonousWeeds, game->snake)) != NULL)
	{
		deleteOne(game->snake); // ���ȼ�һ
		game->score += POISON_SCORE; // �ı�÷�
		// ɾ�����Ե��Ķ���
		o_deleteOne(collidedPos, game->poisonousWeeds);
	}
	if ((collidedPos = checkCollision(game->wisdomGrass, game->snake)) != NULL)
	{
		game->snake->hasWisdom = YES; // ����ӵ���ǻ۲�״̬
		game->score += WISDOM_SCORE; // �ı����
		// ɾ�����Ե����ǻ۲�
		o_deleteOne(collidedPos, game->wisdomGrass);
		o_addObject(game->wisdomGrass); // ����һ���ǻ۲�
	}
}

void updateUI(Game game)
{
	// ������ʱ�������ɽ����������
	drawSnake(game->snake); // ����
	drawObject(game->foods); // ��ʳ��
	drawObject(game->mines); // ������
	if ((GetTickCount() - game->poisonTimer2) > POISON_EXIST_TIME)
	{
		clearObject(game->poisonousWeeds); // ��ⶾ���Ƿ�Ӧ����ʧ
	}
	if (game->poisonTimer1 == YES)
	{
		drawObject(game->poisonousWeeds); // ��˸������
		game->poisonTimer1 = NO;
	}
	else
	{
		game->poisonTimer1 = YES;
	}
	drawObject(game->poisonousWeeds);
	drawObject(game->walls); // ��ǽ
	drawObject(game->wisdomGrass); // ���ǻ۲�
	
}