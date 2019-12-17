#ifndef _GAME_H
#define _GAME_H
#include "snake.h"
#include "interactiveObjects.h"
#include "cJSON.h"
#include <stdio.h>


typedef struct game {
	int score; // ���Ŀǰ�ۼƵ÷�
	Level level; // ��Ϸ���Ѷȣ�Ϊ�������ٶ�
	int screening; // ��Ϸ�Ĺؿ����ؿ������Ѷȿ��ƣ�������������ģ��ؿ���Խ��������Խ�ߣ��ϰ���Խ��
	Snake snake; // ��ҵ���
	// ���ֽ������������
	Food foods;
	PoisonousWeeds poisonousWeeds;
	Mine mines;
	Wall walls;
	WisdomGrass wisdomGrass;
	status isOver; // ��Ϸ�Ƿ������״̬
	status hasWon; // ��ǰ�ؿ��Ƿ�ʤ����״̬
	status poisonTimer1; // ������˸�ļ�ʱ��
	int poisonTimer2; // ���ݴ��ڵļ�ʱ��
}* Game;


status initGame(Game game, Level level);
void nextScreening(Game game);
void newGame(Game game);
Game loadGame(FILE* fp);
FILE* saveGame(Game game);
void checkCollisions(Game game);
void updateUI(Game game);
#endif // !_GAME_H
