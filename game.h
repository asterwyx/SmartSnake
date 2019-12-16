#ifndef _GAME_H
#define _GAME_H
#include "snake.h"
#include "interactiveObjects.h"
#include "cJSON.h"
#include <stdio.h>
typedef enum level {
	EASY,
	MEDIUM,
	HARD
} Level;


typedef struct game {
	// ���Ŀǰ�ۼƵ÷�
	int score;
	// ��Ϸ���Ѷ�
	Level level;
	// ��Ϸ�Ĺؿ����ؿ������Ѷȿ��ƣ�������������ģ��ؿ���Խ��������Խ�ߣ��ϰ���Խ��
	int screening;
	// ��ҵ���
	Snake snake;
	// ���ֽ������������
	Food foods;
	PoisonousWeeds poisonousWeeds;
	Mine mines;
	Wall walls;
	WisdomGrass wisdomGrass;
	
}* Game;


status initGame(Game game, Level level);
void nextScreening(Game game);
void newGame(Game game);
Game loadGame(FILE* fp);
FILE* saveGame(Game game);
#endif // !_GAME_H
