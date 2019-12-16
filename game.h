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
	// 玩家目前累计得分
	int score;
	// 游戏的难度
	Level level;
	// 游戏的关卡，关卡除了难度控制，其他都是随机的，关卡数越高排名就越高，障碍物越多
	int screening;
	// 玩家的蛇
	Snake snake;
	// 各种交互物体的链表
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
