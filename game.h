#ifndef _GAME_H
#define _GAME_H
#include "snake.h"
#include "interactiveObjects.h"
#include "cJSON.h"
#include <stdio.h>


typedef struct game {
	int score; // 玩家目前累计得分
	Level level; // 游戏的难度，为蛇设置速度
	int screening; // 游戏的关卡，关卡除了难度控制，其他都是随机的，关卡数越高排名就越高，障碍物越多
	Snake snake; // 玩家的蛇
	// 各种交互物体的链表
	Food foods;
	PoisonousWeeds poisonousWeeds;
	Mine mines;
	Wall walls;
	WisdomGrass wisdomGrass;
	status isOver; // 游戏是否结束的状态
	status hasWon; // 当前关卡是否胜利的状态
	status poisonTimer1; // 毒草闪烁的计时器
	int poisonTimer2; // 毒草存在的计时器
}* Game;


status initGame(Game game, Level level);
void nextScreening(Game game);
void newGame(Game game);
Game loadGame(FILE* fp);
FILE* saveGame(Game game);
void checkCollisions(Game game);
void updateUI(Game game);
#endif // !_GAME_H
